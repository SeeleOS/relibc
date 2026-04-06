//! `sys/vt.h` implementation.

use crate::platform::types::{c_char, c_short, c_ushort, c_uint};

pub const MIN_NR_CONSOLES: c_uint = 1;
pub const MAX_NR_CONSOLES: c_uint = 63;

pub const VT_OPENQRY: c_uint = 0x5600;
pub const VT_GETMODE: c_uint = 0x5601;
pub const VT_SETMODE: c_uint = 0x5602;
pub const VT_AUTO: c_uint = 0x00;
pub const VT_PROCESS: c_uint = 0x01;
pub const VT_ACKACQ: c_uint = 0x02;
pub const VT_GETSTATE: c_uint = 0x5603;
pub const VT_SENDSIG: c_uint = 0x5604;
pub const VT_RELDISP: c_uint = 0x5605;
pub const VT_ACTIVATE: c_uint = 0x5606;
pub const VT_WAITACTIVE: c_uint = 0x5607;
pub const VT_DISALLOCATE: c_uint = 0x5608;
pub const VT_RESIZE: c_uint = 0x5609;
pub const VT_RESIZEX: c_uint = 0x560A;
pub const VT_LOCKSWITCH: c_uint = 0x560B;
pub const VT_UNLOCKSWITCH: c_uint = 0x560C;
pub const VT_GETHIFONTMASK: c_uint = 0x560D;
pub const VT_WAITEVENT: c_uint = 0x560E;
pub const VT_SETACTIVATE: c_uint = 0x560F;

pub const VT_EVENT_SWITCH: c_uint = 0x0001;
pub const VT_EVENT_BLANK: c_uint = 0x0002;
pub const VT_EVENT_UNBLANK: c_uint = 0x0004;
pub const VT_EVENT_RESIZE: c_uint = 0x0008;
pub const VT_MAX_EVENT: c_uint = 0x000F;

#[repr(C)]
pub struct vt_mode {
    pub mode: c_char,
    pub waitv: c_char,
    pub relsig: c_short,
    pub acqsig: c_short,
    pub frsig: c_short,
}

#[repr(C)]
pub struct vt_stat {
    pub v_active: c_ushort,
    pub v_signal: c_ushort,
    pub v_state: c_ushort,
}

#[repr(C)]
pub struct vt_sizes {
    pub v_rows: c_ushort,
    pub v_cols: c_ushort,
    pub v_scrollsize: c_ushort,
}

#[repr(C)]
pub struct vt_consize {
    pub v_rows: c_ushort,
    pub v_cols: c_ushort,
    pub v_vlin: c_ushort,
    pub v_clin: c_ushort,
    pub v_vcol: c_ushort,
    pub v_ccol: c_ushort,
}

#[repr(C)]
pub struct vt_event {
    pub event: c_uint,
    pub oldev: c_uint,
    pub newev: c_uint,
    pub pad: [c_uint; 4],
}

#[repr(C)]
pub struct vt_setactivate {
    pub console: c_uint,
    pub mode: vt_mode,
}

#[unsafe(no_mangle)]
pub extern "C" fn _cbindgen_export_sys_vt(
    _vt_mode: vt_mode,
    _vt_stat: vt_stat,
    _vt_sizes: vt_sizes,
    _vt_consize: vt_consize,
    _vt_event: vt_event,
    _vt_setactivate: vt_setactivate,
) {
}
