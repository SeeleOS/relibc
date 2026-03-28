//! `sys/utsname.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_utsname.h.html>.

use alloc::string::String;
use crate::{
    error::ResultExt,
    out::Out,
    platform::{
        Pal, Sys,
        types::{c_char, c_int},
    },
};
use seele_sys::misc::SystemInfo;

pub const UTSLENGTH: usize = 65;

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_utsname.h.html>.
#[repr(C)]
#[derive(Clone, Debug, OutProject)]
pub struct utsname {
    pub sysname: [c_char; UTSLENGTH],
    pub nodename: [c_char; UTSLENGTH],
    pub release: [c_char; UTSLENGTH],
    pub version: [c_char; UTSLENGTH],
    pub machine: [c_char; UTSLENGTH],
    pub domainname: [c_char; UTSLENGTH],
}

impl From<SystemInfo> for utsname {
    fn from(value: SystemInfo) -> Self {
        let mut uts = Self {
            sysname: [0; UTSLENGTH],
            nodename: [0; UTSLENGTH],
            release: [0; UTSLENGTH],
            version: [0; UTSLENGTH],
            machine: [0; UTSLENGTH],
            domainname: [0; UTSLENGTH],
        };

        copy_bytes_to_c_chars(&mut uts.sysname, value.name());
        copy_bytes_to_c_chars(&mut uts.release, value.version());
        copy_bytes_to_c_chars(&mut uts.version, value.version());

        uts
    }
}

impl From<utsname> for SystemInfo {
    fn from(value: utsname) -> Self {
        SystemInfo::new(
            &c_chars_to_string(&value.sysname),
            &c_chars_to_string(&value.release),
        )
    }
}

fn copy_bytes_to_c_chars(dst: &mut [c_char], src: &[u8]) {
    let len = src.iter().position(|&b| b == 0).unwrap_or(src.len());
    let len = len.min(dst.len().saturating_sub(1));

    for (dst, src) in dst.iter_mut().zip(src.iter()).take(len) {
        *dst = *src as c_char;
    }
}

fn c_chars_to_string(src: &[c_char]) -> String {
    let len = src.iter().position(|&ch| ch == 0).unwrap_or(src.len());
    let bytes = src[..len].iter().map(|&ch| ch as u8).collect::<alloc::vec::Vec<_>>();
    String::from_utf8_lossy(&bytes).into_owned()
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/uname.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn uname(uts: *mut utsname) -> c_int {
    Sys::uname(unsafe { Out::nonnull(uts) })
        .map(|()| 0)
        .or_minus_one_errno()
}
