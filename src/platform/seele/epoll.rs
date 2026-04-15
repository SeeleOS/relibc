use alloc::{collections::BTreeMap, vec, vec::Vec};
use core::mem;
use seele_sys::{
    syscalls::polling::{
        PollEvent, PollResult, create_poller, poller_add, poller_remove, poller_wait,
    },
    utils::process_result,
};

use super::Sys;
use crate::{
    error::{Errno, Result},
    header::{
        errno::{EEXIST, EINVAL, ENOENT},
        signal::sigset_t,
        sys_epoll::{
            EPOLL_CTL_ADD, EPOLL_CTL_DEL, EPOLL_CTL_MOD, EPOLLET, EPOLLERR, EPOLLHUP, EPOLLIN,
            EPOLLONESHOT, EPOLLOUT, EPOLLPRI, EPOLLRDBAND, EPOLLRDHUP, EPOLLRDNORM,
            EPOLLWRBAND, EPOLLWRNORM, epoll_data, epoll_event,
        },
    },
    platform::{PalEpoll, types::*},
    sync::Mutex,
};

const READABLE_BITS: u32 = EPOLLIN | EPOLLPRI | EPOLLRDNORM | EPOLLRDBAND;
const WRITABLE_BITS: u32 = EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
const DEADLOCK_LOG: bool = false;

#[derive(Clone)]
struct EpollRegistration {
    requested_events: u32,
    data: u64,
    delivered_edge_events: u32,
    disabled: bool,
}

#[derive(Default)]
struct EpollState {
    registrations: BTreeMap<c_int, EpollRegistration>,
}

static EPOLL_REGISTRY: Mutex<BTreeMap<c_int, EpollState>> = Mutex::new(BTreeMap::new());

fn kernel_events_for(bits: u32) -> [Option<PollEvent>; 4] {
    let watch_read = bits & READABLE_BITS != 0;
    let watch_write = bits & WRITABLE_BITS != 0;
    let watch_any = watch_read || watch_write;

    [
        watch_read.then_some(PollEvent::CanBeRead),
        watch_write.then_some(PollEvent::CanBeWritten),
        (watch_any || bits & EPOLLERR != 0).then_some(PollEvent::Error),
        (watch_any || bits & (EPOLLHUP | EPOLLRDHUP) != 0).then_some(PollEvent::Closed),
    ]
}

fn translate_ready_events(requested_events: u32, kernel_events: u32) -> u32 {
    let mut translated = 0;

    if kernel_events & EPOLLIN != 0 {
        translated |= requested_events & READABLE_BITS;
    }
    if kernel_events & EPOLLOUT != 0 {
        translated |= requested_events & WRITABLE_BITS;
    }
    if kernel_events & EPOLLERR != 0 {
        translated |= EPOLLERR;
    }
    if kernel_events & EPOLLHUP != 0 {
        translated |= EPOLLHUP;
        if requested_events & EPOLLRDHUP != 0 {
            translated |= EPOLLRDHUP;
        }
    }

    translated
}

fn sticky_edge_events(ready_events: u32) -> u32 {
    ready_events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)
}

fn unregister_kernel_events(epfd: c_int, fd: c_int) {
    for poll_event in [
        Some(PollEvent::CanBeRead),
        Some(PollEvent::CanBeWritten),
        Some(PollEvent::Error),
        Some(PollEvent::Closed),
    ]
    .into_iter()
    .flatten()
    {
        let _ = super::e_raw(process_result(poller_remove(
            epfd as u64,
            fd as u64,
            poll_event,
        )));
    }
}

pub(super) fn forget_fd(fd: c_int) {
    let removals: Vec<(c_int, c_int)> = {
        let mut registry = EPOLL_REGISTRY.lock();
        let _ = registry.remove(&fd);

        let mut removals = Vec::new();
        for (&epfd, state) in registry.iter_mut() {
            if state.registrations.remove(&fd).is_some() {
                removals.push((epfd, fd));
            }
        }

        removals
    };

    for (epfd, removed_fd) in removals {
        unregister_kernel_events(epfd, removed_fd);
    }
}

impl PalEpoll for Sys {
    fn epoll_create1(flags: c_int) -> Result<c_int> {
        let _ = flags;
        let epfd = super::e_raw(process_result(create_poller())).map(|fd| fd as c_int)?;
        if DEADLOCK_LOG {
            Sys::print_stub_message(format_args!("seele epoll_create1 -> {}\n", epfd));
        }
        EPOLL_REGISTRY
            .lock()
            .entry(epfd)
            .or_insert_with(EpollState::default);
        Ok(epfd)
    }

    unsafe fn epoll_ctl(epfd: c_int, op: c_int, fd: c_int, event: *mut epoll_event) -> Result<()> {
        match op {
            EPOLL_CTL_ADD | EPOLL_CTL_MOD => {
                if event.is_null() {
                    return Err(Errno(EINVAL));
                }

                let event_bits = unsafe { (*event).events };
                if DEADLOCK_LOG {
                    Sys::print_stub_message(format_args!(
                        "seele epoll_ctl op={} epfd={} fd={} events=0x{:x}\n",
                        op, epfd, fd, event_bits
                    ));
                }

                {
                    let mut registry = EPOLL_REGISTRY.lock();
                    let state = registry.get_mut(&epfd).ok_or(Errno(EINVAL))?;
                    let exists = state.registrations.contains_key(&fd);

                    match op {
                        EPOLL_CTL_ADD if exists => return Err(Errno(EEXIST)),
                        EPOLL_CTL_MOD if !exists => return Err(Errno(ENOENT)),
                        _ => {}
                    }

                    state.registrations.insert(
                        fd,
                        EpollRegistration {
                            requested_events: event_bits,
                            data: unsafe { (*event).data.u64 },
                            delivered_edge_events: 0,
                            disabled: false,
                        },
                    );
                }

                unregister_kernel_events(epfd, fd);

                for poll_event in kernel_events_for(event_bits).into_iter().flatten() {
                    super::e_raw(process_result(poller_add(
                        epfd as u64,
                        fd as u64,
                        poll_event,
                        fd as u64,
                    )))?;
                }

                Ok(())
            }
            EPOLL_CTL_DEL => {
                {
                    let mut registry = EPOLL_REGISTRY.lock();
                    let state = registry.get_mut(&epfd).ok_or(Errno(EINVAL))?;
                    if state.registrations.remove(&fd).is_none() {
                        return Err(Errno(ENOENT));
                    }
                }

                if DEADLOCK_LOG {
                    Sys::print_stub_message(format_args!(
                        "seele epoll_ctl op={} epfd={} fd={}\n",
                        op, epfd, fd
                    ));
                }
                unregister_kernel_events(epfd, fd);
                Ok(())
            }
            _ => Err(Errno(EINVAL)),
        }
    }

    unsafe fn epoll_pwait(
        epfd: c_int,
        events: *mut epoll_event,
        maxevents: c_int,
        timeout: c_int,
        sigmask: *const sigset_t,
    ) -> Result<usize> {
        let _ = (timeout, sigmask);
        let _sigsetsize: size_t = mem::size_of::<sigset_t>();

        if maxevents <= 0 {
            return Err(Errno(EINVAL));
        }

        let mut poll_results = vec![PollResult::default(); maxevents as usize];
        if DEADLOCK_LOG {
            Sys::print_stub_message(format_args!(
                "seele epoll_pwait enter epfd={} maxevents={} timeout={}\n",
                epfd, maxevents, timeout
            ));
        }
        let count = super::e_raw(process_result(poller_wait(
            epfd as u64,
            poll_results.as_mut_ptr(),
            maxevents as usize,
            timeout,
        )))?;
        if DEADLOCK_LOG {
            Sys::print_stub_message(format_args!(
                "seele epoll_pwait raw wake epfd={} count={}\n",
                epfd, count
            ));
        }

        let mut ready_by_fd = BTreeMap::<c_int, u32>::new();
        for result in poll_results.into_iter().take(count) {
            ready_by_fd
                .entry(result.data as c_int)
                .and_modify(|events| *events |= result.events)
                .or_insert(result.events);
        }

        let mut registry = EPOLL_REGISTRY.lock();
        let state = registry.get_mut(&epfd).ok_or(Errno(EINVAL))?;

        let mut produced = 0;
        for (fd, kernel_ready) in ready_by_fd {
            if produced >= maxevents as usize {
                break;
            }

            let Some(registration) = state.registrations.get_mut(&fd) else {
                continue;
            };
            if registration.disabled {
                continue;
            }

            let mut ready = translate_ready_events(registration.requested_events, kernel_ready);

            if registration.requested_events & EPOLLET != 0 {
                let sticky_ready = sticky_edge_events(ready);
                ready &= !registration.delivered_edge_events;
                registration.delivered_edge_events |= sticky_ready & ready;
            }

            if ready == 0 {
                continue;
            }

            if registration.requested_events & EPOLLONESHOT != 0 {
                registration.disabled = true;
            }

            unsafe {
                events.add(produced).write(epoll_event {
                    events: ready,
                    data: epoll_data {
                        u64: registration.data,
                    },
                });
            }
            produced += 1;
        }

        if DEADLOCK_LOG {
            Sys::print_stub_message(format_args!(
                "seele epoll_pwait exit epfd={} produced={}\n",
                epfd, produced
            ));
        }

        Ok(produced)
    }
}
