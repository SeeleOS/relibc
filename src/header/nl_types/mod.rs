//! `nl_types.h` implementation.
//!
//! This is a minimal stub for message catalogs. It is sufficient for users of
//! the POSIX interfaces that only need the fallback-string behavior, such as
//! libc++'s `messages` facet during cross builds.

use crate::platform::types::{c_char, c_int};

pub type nl_catd = *mut core::ffi::c_void;

pub const NL_SETD: c_int = 1;
pub const NL_CAT_LOCALE: c_int = 1;

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/catopen.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn catopen(_name: *const c_char, _oflag: c_int) -> nl_catd {
    core::ptr::dangling_mut::<core::ffi::c_void>()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/catgets.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn catgets(
    _catalog: nl_catd,
    _set_number: c_int,
    _message_number: c_int,
    message: *const c_char,
) -> *mut c_char {
    message.cast_mut()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/catclose.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn catclose(_catalog: nl_catd) -> c_int {
    0
}
