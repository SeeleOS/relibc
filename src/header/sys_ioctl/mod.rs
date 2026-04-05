//! ioctl implementation for linux

use crate::platform::types::{c_char, c_uint, c_ulong, c_ushort};

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

#[repr(C)]
#[derive(Clone, Copy, Default)]
pub struct fb_bitfield {
    pub offset: c_uint,
    pub length: c_uint,
    pub msb_right: c_uint,
}

#[repr(C)]
#[derive(Clone, Copy)]
pub struct fb_fix_screeninfo {
    pub id: [c_char; 16],
    pub smem_start: c_ulong,
    pub smem_len: c_uint,
    pub type_: c_uint,
    pub type_aux: c_uint,
    pub visual: c_uint,
    pub xpanstep: c_ushort,
    pub ypanstep: c_ushort,
    pub ywrapstep: c_ushort,
    pub line_length: c_uint,
    pub mmio_start: c_ulong,
    pub mmio_len: c_uint,
    pub accel: c_uint,
    pub capabilities: c_ushort,
    pub reserved: [c_ushort; 2],
}

impl Default for fb_fix_screeninfo {
    fn default() -> Self {
        Self {
            id: [0; 16],
            smem_start: 0,
            smem_len: 0,
            type_: 0,
            type_aux: 0,
            visual: 0,
            xpanstep: 0,
            ypanstep: 0,
            ywrapstep: 0,
            line_length: 0,
            mmio_start: 0,
            mmio_len: 0,
            accel: 0,
            capabilities: 0,
            reserved: [0; 2],
        }
    }
}

#[repr(C)]
#[derive(Clone, Copy, Default)]
pub struct fb_var_screeninfo {
    pub xres: c_uint,
    pub yres: c_uint,
    pub xres_virtual: c_uint,
    pub yres_virtual: c_uint,
    pub xoffset: c_uint,
    pub yoffset: c_uint,
    pub bits_per_pixel: c_uint,
    pub grayscale: c_uint,
    pub red: fb_bitfield,
    pub green: fb_bitfield,
    pub blue: fb_bitfield,
    pub transp: fb_bitfield,
    pub nonstd: c_uint,
    pub activate: c_uint,
    pub height: c_uint,
    pub width: c_uint,
    pub accel_flags: c_uint,
    pub pixclock: c_uint,
    pub left_margin: c_uint,
    pub right_margin: c_uint,
    pub upper_margin: c_uint,
    pub lower_margin: c_uint,
    pub hsync_len: c_uint,
    pub vsync_len: c_uint,
    pub sync: c_uint,
    pub vmode: c_uint,
    pub rotate: c_uint,
    pub colorspace: c_uint,
    pub reserved: [c_uint; 4],
}

#[repr(C)]
#[derive(Clone, Copy, Default)]
pub struct fb_cmap {
    pub start: c_uint,
    pub len: c_uint,
    pub red: *mut c_ushort,
    pub green: *mut c_ushort,
    pub blue: *mut c_ushort,
    pub transp: *mut c_ushort,
}

#[cfg(any(target_os = "linux", target_os = "seele"))]
pub use self::linux::*;

#[cfg(any(target_os = "linux", target_os = "seele"))]
pub mod linux;

#[cfg(target_os = "redox")]
pub use self::redox::*;

#[cfg(target_os = "redox")]
pub mod redox;
