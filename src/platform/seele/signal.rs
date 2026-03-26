use seele_sys::{
    signal::{Signal, SignalAction, SignalHandlingType, Signals},
    syscalls::signal::{register_signal_action, send_signal},
    utils::process_result,
};

use crate::{
    header::{errno::EINVAL, netdb::protoent, signal::sigval},
    platform::{Pal, sys::e_raw},
};
use core::mem;

use super::{
    super::{PalSignal, types::*},
    Sys,
};
use crate::{
    error::{Errno, Result},
    header::{
        bits_time::timespec,
        signal::{SI_QUEUE, SIG_DFL, SIG_IGN, sigaction, siginfo_t, sigset_t, stack_t},
        sys_time::itimerval,
    },
};

impl From<&SignalAction> for sigaction {
    fn from(action: &SignalAction) -> Self {
        let sa_handler = match action.handling_type {
            SignalHandlingType::Default => unsafe { core::mem::transmute(SIG_DFL) },
            SignalHandlingType::Ignore => unsafe { core::mem::transmute(SIG_IGN) },
            SignalHandlingType::Function(function) => Some(function),
        };

        Self {
            sa_handler,
            sa_flags: 0,
            sa_restorer: None,
            sa_mask: action.ignored_signals.bits(),
        }
    }
}

impl From<&sigaction> for SignalAction {
    fn from(action: &sigaction) -> Self {
        let handling_type = match action.sa_handler.map(|handler| handler as usize) {
            Some(SIG_DFL) | None => SignalHandlingType::Default,
            Some(SIG_IGN) => SignalHandlingType::Ignore,
            Some(_) => SignalHandlingType::Function(action.sa_handler.unwrap()),
        };

        Self {
            handling_type,
            ignored_signals: Signals::from_bits_retain(action.sa_mask),
        }
    }
}

impl PalSignal for Sys {
    fn getitimer(which: c_int, out: &mut itimerval) -> Result<()> {
        let _ = (which, out);
        Sys::stub("GETITIMER").map(|_| ())
    }

    fn kill(pid: pid_t, sig: c_int) -> Result<()> {
        e_raw(process_result(send_signal(
            pid as u64,
            Signal::try_from(sig as u64).map_err(|_| Errno(EINVAL))?,
        )))
        .map(|_| ())
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
        if sig == 9 || sig == 19 {
            return Err(Errno(22));
        }

        let signal = Signal::try_from(sig as u64).map_err(|_| Errno(EINVAL))?;
        let new_action = act.map(SignalAction::from);
        let mut old_action = oact.as_ref().map(|_| SignalAction::default());

        e_raw(process_result(register_signal_action(
            signal,
            new_action
                .as_ref()
                .map_or(core::ptr::null(), |action| action as *const SignalAction),
            old_action
                .as_mut()
                .map_or(core::ptr::null_mut(), |action| action as *mut SignalAction),
        )))?;

        if let (Some(oact), Some(old_action)) = (oact, old_action.as_ref()) {
            *oact = sigaction::from(old_action);
        }

        Ok(())
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
        let _sigsetsize = mem::size_of::<sigset_t>();
        Sys::sigprocmask_stub(how, set, oset)
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
