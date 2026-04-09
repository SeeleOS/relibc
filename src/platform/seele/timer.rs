use super::Sys;
use crate::{
    error::Result,
    header::{signal::sigevent, time::itimerspec},
    out::Out,
    platform::types::{c_int, clockid_t, timer_t},
};

pub(super) fn timer_create(
    clock_id: clockid_t,
    evp: &sigevent,
    mut timerid: Out<timer_t>,
) -> Result<()> {
    let _ = (clock_id, evp);
    if !timerid.as_mut_ptr().is_null() {
        unsafe {
            *timerid.as_mut_ptr() = core::ptr::null_mut();
        }
    }
    Sys::stub("TIMER_CREATE").map(|_| ())
}

pub(super) fn timer_delete(timerid: timer_t) -> Result<()> {
    let _ = timerid;
    Sys::stub("TIMER_DELETE").map(|_| ())
}

pub(super) fn timer_gettime(timerid: timer_t, mut value: Out<itimerspec>) -> Result<()> {
    let _ = (timerid, value.as_mut_ptr());
    Sys::stub("TIMER_GETTIME").map(|_| ())
}

pub(super) fn timer_settime(
    timerid: timer_t,
    flags: c_int,
    value: &itimerspec,
    ovalue: Option<Out<itimerspec>>,
) -> Result<()> {
    let _ = (timerid, flags, value, ovalue);
    Sys::stub("TIMER_SETTIME").map(|_| ())
}
