//! `sys/wait.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_wait.h.html>.

use crate::{
    error::ResultExt,
    header::signal::siginfo_t,
    out::Out,
    platform::{
        self,
        Pal, Sys,
        types::{c_int, id_t, pid_t},
    },
};

pub const WNOHANG: c_int = 1;
pub const WUNTRACED: c_int = 2;

pub const WSTOPPED: c_int = 2;
pub const WEXITED: c_int = 4;
pub const WCONTINUED: c_int = 8;
pub const WNOWAIT: c_int = 0x0100_0000;

pub const __WNOTHREAD: c_int = 0x2000_0000;
pub const __WALL: c_int = 0x4000_0000;
#[allow(overflowing_literals)]
pub const __WCLONE: c_int = 0x8000_0000;

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wait.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wait(stat_loc: *mut c_int) -> pid_t {
    unsafe { waitpid(!0, stat_loc, 0) }
}

pub type idtype_t = c_int;

pub const P_ALL: idtype_t = 0;
pub const P_PID: idtype_t = 1;
pub const P_PGID: idtype_t = 2;

#[unsafe(no_mangle)]
pub unsafe extern "C" fn waitid(
    idtype: idtype_t,
    id: id_t,
    infop: *mut siginfo_t,
    options: c_int,
) -> c_int {
    let pid = match idtype {
        P_ALL => !0,
        P_PID => id as pid_t,
        P_PGID => -(id as pid_t),
        _ => {
            platform::ERRNO.set(crate::header::errno::EINVAL);
            return -1;
        }
    };

    let mut status = 0;
    let waited = Sys::waitpid(pid, Some(Out::from_mut(&mut status)), options).or_minus_one_errno();
    if waited < 0 {
        return -1;
    }

    if !infop.is_null() {
        unsafe {
            *infop = siginfo_t {
                si_signo: 0,
                si_errno: 0,
                si_code: 0,
                si_pid: waited,
                si_uid: 0,
                si_addr: core::ptr::null_mut(),
                si_status: status,
                si_value: crate::header::signal::sigval { sival_int: 0 },
            };
        }
    }

    0
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/waitpid.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn waitpid(pid: pid_t, stat_loc: *mut c_int, options: c_int) -> pid_t {
    Sys::waitpid(pid, unsafe { Out::nullable(stat_loc) }, options).or_minus_one_errno()
}
