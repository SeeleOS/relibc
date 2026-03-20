//! ioctl implementation for linux

use crate::platform::types::{c_char, c_ushort};

// This is used from sgtty
#[repr(C)]
pub struct sgttyb {
    sg_ispeed: c_char,
    sg_ospeed: c_char,
    sg_erase: c_char,
    sg_kill: c_char,
    sg_flags: c_ushort,
}

#[repr(C)]
#[derive(Default)]
pub struct winsize {
    pub ws_row: c_ushort,
    pub ws_col: c_ushort,
    pub ws_xpixel: c_ushort,
    pub ws_ypixel: c_ushort,
}

impl winsize {
    pub fn get_row_col(&self) -> (c_ushort, c_ushort) {
        (self.ws_row, self.ws_col)
    }
}

#[cfg(any(target_os = "linux", target_os = "seele"))]
pub use self::linux::*;

#[cfg(any(target_os = "linux", target_os = "seele"))]
pub mod linux;

#[cfg(target_os = "redox")]
pub use self::redox::*;

#[cfg(target_os = "redox")]
pub mod redox;
