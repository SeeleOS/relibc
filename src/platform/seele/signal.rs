use crate::{header::signal::sigval, platform::Pal};
use core::mem;

use super::{
    super::{PalSignal, types::*},
    Sys,
};
use crate::{
    error::{Errno, Result},
    header::{
        bits_time::timespec,
        signal::{SI_QUEUE, sigaction, siginfo_t, sigset_t, stack_t},
        sys_time::itimerval,
    },
};

impl PalSignal for Sys {
    fn getitimer(which: c_int, out: &mut itimerval) -> Result<()> {
        let _ = (which, out);
        Sys::stub("GETITIMER").map(|_| ())
    }

    fn kill(pid: pid_t, sig: c_int) -> Result<()> {
        let _ = (pid, sig);
        Sys::stub("KILL").map(|_| ())
    }
    fn sigqueue(pid: pid_t, sig: c_int, val: sigval) -> Result<()> {
        let _ = (pid, sig, val);
        let _info = siginfo_t {
            si_addr: core::ptr::null_mut(),
            si_code: SI_QUEUE,
            si_errno: 0,
            si_pid: 0,
            si_signo: sig,
            si_status: 0,
            si_uid: 0,
            si_value: val,
        };
        Sys::stub("RT_SIGQUEUEINFO").map(|_| ())
    }

    fn killpg(pgrp: pid_t, sig: c_int) -> Result<()> {
        let _ = (pgrp, sig);
        Sys::stub("KILL").map(|_| ())
    }

    fn raise(sig: c_int) -> Result<()> {
        let _ = sig;
        let _tid = Sys::gettid() as pid_t;
        Sys::stub("TKILL").map(|_| ())
    }

    fn setitimer(which: c_int, new: &itimerval, old: Option<&mut itimerval>) -> Result<()> {
        let _ = (which, new, old);
        Sys::stub("SETITIMER").map(|_| ())
    }

    fn sigaction(
        sig: c_int,
        act: Option<&sigaction>,
        oact: Option<&mut sigaction>,
    ) -> Result<(), Errno> {
        let _ = (sig, act, oact);
        Sys::stub("RT_SIGACTION").map(|_| ())
    }

    unsafe fn sigaltstack(ss: Option<&stack_t>, old_ss: Option<&mut stack_t>) -> Result<()> {
        let _ = (ss, old_ss);
        Sys::stub("SIGALTSTACK").map(|_| ())
    }

    fn sigpending(set: &mut sigset_t) -> Result<()> {
        let _ = set;
        let _sigsetsize = mem::size_of::<sigset_t>();
        Sys::stub("RT_SIGPENDING").map(|_| ())
    }

    fn sigprocmask(how: c_int, set: Option<&sigset_t>, oset: Option<&mut sigset_t>) -> Result<()> {
        let _ = (how, set, oset);
        let _sigsetsize = mem::size_of::<sigset_t>();
        Sys::stub("RT_SIGPROCMASK").map(|_| ())
    }

    fn sigsuspend(mask: &sigset_t) -> Errno {
        let _ = mask;
        let _sigsetsize = size_of::<sigset_t>();
        Sys::stub("RT_SIGSUSPEND").err().unwrap_or(Errno(0))
    }

    fn sigtimedwait(
        set: &sigset_t,
        sig: Option<&mut siginfo_t>,
        tp: Option<&timespec>,
    ) -> Result<c_int> {
        let _ = (set, sig, tp);
        let _sigsetsize = size_of::<sigset_t>();
        Ok(Sys::stub("RT_SIGTIMEDWAIT")? as c_int)
    }
}
