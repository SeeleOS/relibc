//! `sys/kd.h` implementation.

use crate::platform::types::{c_char, c_int, c_uchar, c_uint, c_ushort};

pub const KIOCSOUND: c_int = 0x4B2F;
pub const KDMKTONE: c_int = 0x4B30;

pub const KDGETLED: c_int = 0x4B31;
pub const KDSETLED: c_int = 0x4B32;
pub const LED_SCR: c_int = 0x01;
pub const LED_NUM: c_int = 0x02;
pub const LED_CAP: c_int = 0x04;

pub const KDGKBTYPE: c_int = 0x4B33;
pub const KB_84: c_int = 0x01;
pub const KB_101: c_int = 0x02;
pub const KB_OTHER: c_int = 0x03;

pub const KDADDIO: c_int = 0x4B34;
pub const KDDELIO: c_int = 0x4B35;
pub const KDENABIO: c_int = 0x4B36;
pub const KDDISABIO: c_int = 0x4B37;

pub const KDSETMODE: c_int = 0x4B3A;
pub const KD_TEXT: c_int = 0x00;
pub const KD_GRAPHICS: c_int = 0x01;
pub const KD_TEXT0: c_int = 0x02;
pub const KD_TEXT1: c_int = 0x03;
pub const KDGETMODE: c_int = 0x4B3B;

pub const GIO_SCRNMAP: c_int = 0x4B40;
pub const PIO_SCRNMAP: c_int = 0x4B41;

pub const K_RAW: c_int = 0x00;
pub const K_XLATE: c_int = 0x01;
pub const K_MEDIUMRAW: c_int = 0x02;
pub const K_UNICODE: c_int = 0x03;
pub const K_OFF: c_int = 0x04;
pub const KDGKBMODE: c_int = 0x4B44;
pub const KDSKBMODE: c_int = 0x4B45;

pub const KDGKBENT: c_int = 0x4B46;
pub const KDSKBENT: c_int = 0x4B47;

#[repr(C)]
pub struct consolefontdesc {
    pub charcount: c_ushort,
    pub charheight: c_ushort,
    pub chardata: *mut c_char,
}

#[repr(C)]
pub struct unipair {
    pub unicode: c_ushort,
    pub fontpos: c_ushort,
}

#[repr(C)]
pub struct unimapdesc {
    pub entry_ct: c_ushort,
    pub entries: *mut unipair,
}

#[repr(C)]
pub struct unimapinit {
    pub advised_hashsize: c_ushort,
    pub advised_hashstep: c_ushort,
    pub advised_hashlevel: c_ushort,
}

#[repr(C)]
pub struct kbentry {
    pub kb_table: c_uchar,
    pub kb_index: c_uchar,
    pub kb_value: c_ushort,
}

#[repr(C)]
pub struct kbsentry {
    pub kb_func: c_uchar,
    pub kb_string: [c_uchar; 512],
}

#[repr(C)]
pub struct kbdiacr {
    pub diacr: c_uchar,
    pub base: c_uchar,
    pub result: c_uchar,
}

#[repr(C)]
pub struct kbdiacrs {
    pub kb_cnt: c_uint,
    pub kbdiacr: [kbdiacr; 256],
}

#[repr(C)]
pub struct kbdiacruc {
    pub diacr: c_uint,
    pub base: c_uint,
    pub result: c_uint,
}

#[repr(C)]
pub struct kbdiacrsuc {
    pub kb_cnt: c_uint,
    pub kbdiacruc: [kbdiacruc; 256],
}

#[repr(C)]
pub struct kbkeycode {
    pub scancode: c_uint,
    pub keycode: c_uint,
}

#[repr(C)]
pub struct kbd_repeat {
    pub delay: c_int,
    pub period: c_int,
}

#[repr(C)]
pub struct console_font_op {
    pub op: c_uint,
    pub flags: c_uint,
    pub width: c_uint,
    pub height: c_uint,
    pub charcount: c_uint,
    pub data: *mut c_uchar,
}

#[repr(C)]
pub struct console_font {
    pub width: c_uint,
    pub height: c_uint,
    pub charcount: c_uint,
    pub data: *mut c_uchar,
}

#[unsafe(no_mangle)]
pub extern "C" fn _cbindgen_export_sys_kd(
    _consolefontdesc: consolefontdesc,
    _unipair: unipair,
    _unimapdesc: unimapdesc,
    _unimapinit: unimapinit,
    _kbentry: kbentry,
    _kbsentry: kbsentry,
    _kbdiacr: kbdiacr,
    _kbdiacrs: kbdiacrs,
    _kbdiacruc: kbdiacruc,
    _kbdiacrsuc: kbdiacrsuc,
    _kbkeycode: kbkeycode,
    _kbd_repeat: kbd_repeat,
    _console_font_op: console_font_op,
    _console_font: console_font,
) {
}
