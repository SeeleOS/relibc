//! `sys/ipc.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_ipc.h.html>.

use crate::{
    c_str::CStr,
    error::ResultExt,
    header::sys_stat,
    platform::types::{c_char, c_int, c_uint, gid_t, key_t, mode_t, uid_t},
};

pub const IPC_CREAT: c_int = 0o1000;
pub const IPC_EXCL: c_int = 0o2000;
pub const IPC_NOWAIT: c_int = 0o4000;

pub const IPC_PRIVATE: key_t = 0;

pub const IPC_RMID: c_int = 0;
pub const IPC_SET: c_int = 1;
pub const IPC_STAT: c_int = 2;

pub const IPC_INFO: c_int = 3;
pub const MSG_STAT: c_int = 11;
pub const MSG_INFO: c_int = 12;
pub const SEM_STAT: c_int = 18;
pub const SEM_INFO: c_int = 19;
pub const SHM_STAT: c_int = 13;
pub const SHM_INFO: c_int = 14;

#[repr(C)]
#[derive(Default)]
pub struct ipc_perm {
    pub __key: key_t,
    pub uid: uid_t,
    pub gid: gid_t,
    pub cuid: uid_t,
    pub cgid: gid_t,
    pub mode: mode_t,
    pub __seq: c_uint,
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ftok.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn ftok(path: *const c_char, id: c_int) -> key_t {
    let path = unsafe { CStr::from_ptr(path) };
    let mut st = sys_stat::stat::default();

    if unsafe { sys_stat::stat(path.as_ptr(), &mut st) } < 0 {
        return -1;
    }

    ((id & 0xff) << 24) | ((st.st_dev as c_int & 0xff) << 16) | (st.st_ino as c_int & 0xffff)
}
