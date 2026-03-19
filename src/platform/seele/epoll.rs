use alloc::vec;
use core::mem;
use seele_syslib::{
    syscalls::polling::{PollEvent, PollResult, create_poller, poller_add, poller_remove, poller_wait},
    utils::process_result,
};

use super::Sys;
use crate::{
    error::{Errno, Result},
    header::{
        errno::EINVAL,
        signal::sigset_t,
        sys_epoll::{EPOLLERR, EPOLLHUP, EPOLLIN, EPOLLOUT, EPOLL_CTL_ADD, EPOLL_CTL_DEL, EPOLL_CTL_MOD, epoll_event},
    },
    platform::{PalEpoll, types::*},
};

fn epoll_bits_to_poll_events(bits: u32) -> [Option<PollEvent>; 4] {
    [
        (bits & EPOLLIN != 0).then_some(PollEvent::CanBeRead),
        (bits & EPOLLOUT != 0).then_some(PollEvent::CanBeWritten),
        (bits & EPOLLERR != 0).then_some(PollEvent::Error),
        (bits & EPOLLHUP != 0).then_some(PollEvent::Closed),
    ]
}

impl PalEpoll for Sys {
    fn epoll_create1(flags: c_int) -> Result<c_int> {
        let _ = flags;
        super::e_raw(process_result(create_poller())).map(|fd| fd as c_int)
    }

    unsafe fn epoll_ctl(epfd: c_int, op: c_int, fd: c_int, event: *mut epoll_event) -> Result<()> {
        match op {
            EPOLL_CTL_ADD | EPOLL_CTL_MOD => {
                if event.is_null() {
                    return Err(Errno(EINVAL));
                }

                let event_bits = unsafe { (*event).events };
                if op == EPOLL_CTL_MOD {
                    for poll_event in epoll_bits_to_poll_events(EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP)
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

                for poll_event in epoll_bits_to_poll_events(event_bits).into_iter().flatten() {
                    super::e_raw(process_result(poller_add(
                        epfd as u64,
                        fd as u64,
                        poll_event,
                    )))?;
                }

                Ok(())
            }
            EPOLL_CTL_DEL => {
                for poll_event in epoll_bits_to_poll_events(EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP)
                    .into_iter()
                    .flatten()
                {
                    let _ = super::e_raw(process_result(poller_remove(
                        epfd as u64,
                        fd as u64,
                        poll_event,
                    )));
                }

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
        let count = super::e_raw(process_result(poller_wait(
            epfd as u64,
            poll_results.as_mut_ptr(),
            maxevents as usize,
        )))?;

        for (index, result) in poll_results.into_iter().take(count).enumerate() {
            unsafe {
                events.add(index).write(epoll_event {
                    events: result.events,
                    data: crate::header::sys_epoll::epoll_data {
                        u64: result.data,
                    },
                });
            }
        }

        Ok(count)
    }
}
