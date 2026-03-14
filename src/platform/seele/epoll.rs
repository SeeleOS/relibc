use core::mem;

use super::Sys;
use crate::{
    error::Result,
    header::{signal::sigset_t, sys_epoll::epoll_event},
    platform::{PalEpoll, types::*},
};

impl PalEpoll for Sys {
    fn epoll_create1(flags: c_int) -> Result<c_int> {
        Ok(Sys::stub("EPOLL_CREATE1")? as c_int)
    }

    unsafe fn epoll_ctl(epfd: c_int, op: c_int, fd: c_int, event: *mut epoll_event) -> Result<()> {
        let _ = (epfd, op, fd, event);
        Sys::stub("EPOLL_CTL").map(|_| ())
    }

    unsafe fn epoll_pwait(
        epfd: c_int,
        events: *mut epoll_event,
        maxevents: c_int,
        timeout: c_int,
        sigmask: *const sigset_t,
    ) -> Result<usize> {
        let _ = (epfd, events, maxevents, timeout, sigmask);
        let _sigsetsize: size_t = mem::size_of::<sigset_t>();
        Sys::stub("EPOLL_PWAIT")
    }
}
