//! `sched.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.

use crate::{
    error::ResultExt,
    header::errno::{EINVAL, ENOSYS},
    header::bits_time::timespec,
    platform::{
        self,
        Pal, Sys,
        types::{c_int, pid_t, size_t},
    },
};

// TODO: There are extensions, but adding more member is breaking ABI for pthread_attr_t
/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub struct sched_param {
    pub sched_priority: c_int,
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
pub const SCHED_FIFO: c_int = 0;
/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
pub const SCHED_RR: c_int = 1;
/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
pub const SCHED_OTHER: c_int = 2;

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_get_priority_max.html>.
// #[unsafe(no_mangle)]
pub extern "C" fn sched_get_priority_max(policy: c_int) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_get_priority_max.html>.
// #[unsafe(no_mangle)]
pub extern "C" fn sched_get_priority_min(policy: c_int) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_getparam.html>.
// #[unsafe(no_mangle)]
pub unsafe extern "C" fn sched_getparam(pid: pid_t, param: *mut sched_param) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_rr_get_interval.html>.
// #[unsafe(no_mangle)]
pub extern "C" fn sched_rr_get_interval(pid: pid_t, time: *const timespec) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_setparam.html>.
// #[unsafe(no_mangle)]
pub unsafe extern "C" fn sched_setparam(pid: pid_t, param: *const sched_param) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_setscheduler.html>.
// #[unsafe(no_mangle)]
pub extern "C" fn sched_setscheduler(
    pid: pid_t,
    policy: c_int,
    param: *const sched_param,
) -> c_int {
    todo!()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_yield.html>.
#[unsafe(no_mangle)]
pub extern "C" fn sched_yield() -> c_int {
    Sys::sched_yield().map(|()| 0).or_minus_one_errno()
}

/// Linux extension. Report a single available CPU until the kernel grows a real affinity API.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn sched_getaffinity(
    pid: pid_t,
    cpusetsize: size_t,
    mask: *mut core::ffi::c_void,
) -> c_int {
    if pid != 0 && pid != Sys::getpid() {
        platform::ERRNO.set(ENOSYS);
        return -1;
    }
    if mask.is_null() || cpusetsize == 0 {
        platform::ERRNO.set(EINVAL);
        return -1;
    }

    let bytes = unsafe { core::slice::from_raw_parts_mut(mask.cast::<u8>(), cpusetsize) };
    bytes.fill(0);
    bytes[0] = 1;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn cbindgen_stupid_struct_user_for_sched_param(_: sched_param) {}
