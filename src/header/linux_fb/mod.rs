//! `linux/fb.h` implementation.
//!
//! Non-POSIX.

use crate::platform::types::{c_char, c_uint, c_ulong, c_ushort};

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
    pub r#type: c_uint,
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
            r#type: 0,
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

pub const FBIOGET_VSCREENINFO: c_ulong = 0x4600;
pub const FBIOPUT_VSCREENINFO: c_ulong = 0x4601;
pub const FBIOGET_FSCREENINFO: c_ulong = 0x4602;
pub const FBIOGETCMAP: c_ulong = 0x4604;
pub const FBIOPUTCMAP: c_ulong = 0x4605;
pub const FBIOPAN_DISPLAY: c_ulong = 0x4606;
pub const FBIOBLANK: c_ulong = 0x4611;

pub const FB_TYPE_PACKED_PIXELS: c_uint = 0;
pub const FB_TYPE_PLANES: c_uint = 1;
pub const FB_TYPE_INTERLEAVED_PLANES: c_uint = 2;
pub const FB_TYPE_TEXT: c_uint = 3;
pub const FB_TYPE_VGA_PLANES: c_uint = 4;
pub const FB_TYPE_FOURCC: c_uint = 5;

pub const FB_VISUAL_MONO01: c_uint = 0;
pub const FB_VISUAL_MONO10: c_uint = 1;
pub const FB_VISUAL_TRUECOLOR: c_uint = 2;
pub const FB_VISUAL_PSEUDOCOLOR: c_uint = 3;
pub const FB_VISUAL_DIRECTCOLOR: c_uint = 4;
pub const FB_VISUAL_STATIC_PSEUDOCOLOR: c_uint = 5;
pub const FB_VISUAL_FOURCC: c_uint = 6;

pub const FB_ACTIVATE_NOW: c_uint = 0;
pub const FB_ACTIVATE_NXTOPEN: c_uint = 1;
pub const FB_ACTIVATE_TEST: c_uint = 2;
pub const FB_ACTIVATE_MASK: c_uint = 15;
pub const FB_ACTIVATE_VBL: c_uint = 16;
pub const FB_CHANGE_CMAP_VBL: c_uint = 32;
pub const FB_ACTIVATE_ALL: c_uint = 64;
pub const FB_ACTIVATE_FORCE: c_uint = 128;
pub const FB_ACTIVATE_INV_MODE: c_uint = 256;

pub const FB_ACCELF_TEXT: c_uint = 1;

pub const FB_SYNC_HOR_HIGH_ACT: c_uint = 1;
pub const FB_SYNC_VERT_HIGH_ACT: c_uint = 2;
pub const FB_SYNC_EXT: c_uint = 4;
pub const FB_SYNC_COMP_HIGH_ACT: c_uint = 8;
pub const FB_SYNC_BROADCAST: c_uint = 16;
pub const FB_SYNC_ON_GREEN: c_uint = 32;

pub const FB_VMODE_NONINTERLACED: c_uint = 0;
pub const FB_VMODE_INTERLACED: c_uint = 1;
pub const FB_VMODE_DOUBLE: c_uint = 2;
pub const FB_VMODE_ODD_FLD_FIRST: c_uint = 4;
pub const FB_VMODE_MASK: c_uint = 255;
pub const FB_VMODE_YWRAP: c_uint = 256;
pub const FB_VMODE_SMOOTH_XPAN: c_uint = 512;
pub const FB_VMODE_CONUPDATE: c_uint = 512;
