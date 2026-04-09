//! `sys/sysinfo.h` implementation.
//!
//! This is a Linux compatibility interface rather than a POSIX header.

use crate::{
    out::Out,
    platform::types::{c_char, c_int, c_long, c_uint, c_ulong, c_ushort},
};

#[repr(C)]
#[derive(Default)]
pub struct sysinfo {
    pub uptime: c_long,
    pub loads: [c_ulong; 3],
    pub totalram: c_ulong,
    pub freeram: c_ulong,
    pub sharedram: c_ulong,
    pub bufferram: c_ulong,
    pub totalswap: c_ulong,
    pub freeswap: c_ulong,
    pub procs: c_ushort,
    pub totalhigh: c_ulong,
    pub freehigh: c_ulong,
    pub mem_unit: c_uint,
    #[cfg(target_pointer_width = "32")]
    pub _f: [c_char; 8],
    #[cfg(target_pointer_width = "64")]
    pub _f: [c_char; 0],
}

pub extern "C" fn _cbindgen_export_sysinfo(info: sysinfo) {
    let _ = info;
}

/// Minimal Linux-compatible `sysinfo()` stub.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn sysinfo(info: *mut sysinfo) -> c_int {
    let mut out = unsafe { Out::nonnull(info) };
    out.write(sysinfo {
        mem_unit: 1,
        ..Default::default()
    });
    0
}
