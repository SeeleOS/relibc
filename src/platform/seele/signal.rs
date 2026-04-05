use seele_sys::{
    errors::SyscallError,
    signal::{SigHandlerFn2, Signal, SignalAction, SignalHandlingType, Signals},
    syscalls::{
        get_process_id,
        signal::{
            block_signals, register_signal_action, send_signal, set_blocked_signals,
            sig_handler_return, unblock_signals,
        },
    },
    utils::process_result,
};

use crate::{
    header::{
        errno::EINVAL,
        netdb::protoent,
        signal::{
            SA_RESTORER, SA_SIGINFO, SIG_BLOCK, SIG_SETMASK, SIG_UNBLOCK, SIGKILL, SIGSTOP, kill,
            sigval,
        },
        unistd::getpid,
    },
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

unsafe extern "C" fn __seele_restore_rt() {
    let _ = sig_handler_return();
    unsafe { core::hint::unreachable_unchecked() }
}

impl From<&SignalAction> for sigaction {
    fn from(action: &SignalAction) -> Self {
        let sa_handler = match action.handling_type {
            SignalHandlingType::Default => unsafe { core::mem::transmute(SIG_DFL) },
            SignalHandlingType::Ignore => unsafe { core::mem::transmute(SIG_IGN) },
            SignalHandlingType::Function1(function) => Some(function),
            SignalHandlingType::Function2(function) => unsafe {
                core::mem::transmute::<Option<SigHandlerFn2>, Option<extern "C" fn(c_int)>>(Some(
                    function,
                ))
            },
        };

        Self {
            sa_handler,
            sa_flags: action.flags as c_int,
            sa_restorer: if action.restorer == 0 {
                None
            } else {
                unsafe {
                    Some(core::mem::transmute::<usize, unsafe extern "C" fn()>(
                        action.restorer,
                    ))
                }
            },
            sa_mask: action.sig_handler_ignored_sigs.bits(),
        }
    }
}

impl From<&sigaction> for SignalAction {
    fn from(action: &sigaction) -> Self {
        let handling_type = match action.sa_handler.map(|handler| handler as usize) {
            Some(SIG_DFL) | None => SignalHandlingType::Default,
            Some(SIG_IGN) => SignalHandlingType::Ignore,
            Some(_) if (action.sa_flags as usize & SA_SIGINFO) != 0 => {
                SignalHandlingType::Function2(unsafe {
                    core::mem::transmute::<usize, SigHandlerFn2>(action.sa_handler.unwrap() as usize)
                })
            }
            Some(_) => SignalHandlingType::Function1(action.sa_handler.unwrap()),
        };

        Self {
            handling_type,
            sig_handler_ignored_sigs: Signals::from_bits_retain(action.sa_mask),
            flags: action.sa_flags as u64,
            restorer: action
                .sa_restorer
                .unwrap_or(__seele_restore_rt as unsafe extern "C" fn())
                as usize,
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

    fn alarm(seconds: c_uint) -> c_uint {
        Sys::stub("ALARM");
        0
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
        kill(getpid(), sig);
        Ok(())
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
        let new_action = act.map(|action| {
            let mut action = action.clone();
            action.sa_flags |= SA_RESTORER as c_int;
            action.sa_restorer = Some(__seele_restore_rt);
            SignalAction::from(&action)
        });
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
        let signals = if let Some(set) = set {
            Signals::from_bits(*set)
        } else {
            Signals::from_bits(0)
        };

        let mut signals = signals.ok_or(Errno(EINVAL))?;
        signals.remove(Signals::from(
            Signal::try_from(SIGKILL as u64).map_err(|_| Errno(EINVAL))?,
        ));
        signals.remove(Signals::from(
            Signal::try_from(SIGSTOP as u64).map_err(|_| Errno(EINVAL))?,
        ));

        let old_signals = &mut Signals::default() as *mut Signals;

        let result = e_raw(process_result(match how {
            SIG_BLOCK => block_signals((signals), old_signals),
            SIG_UNBLOCK => unblock_signals((signals), old_signals),
            SIG_SETMASK => set_blocked_signals(signals, old_signals),
            _ => Err(SyscallError::InvalidArguments),
        }))
        .map(|_| ());

        if let Some(oset) = oset {
            unsafe {
                *oset = (*old_signals).bits();
            }
        }

        result
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
