use alloc::ffi::CString;
use core::slice;

use seele_sys::{
    abi::object::{ControlCommand, ObjectFlags},
    syscalls::{
        object::control_object,
        socket::{
            accept as socket_accept, bind as socket_bind, connect as socket_connect,
            listen as socket_listen, socket as create_socket,
        },
    },
    utils::process_result,
};

use super::{Sys, e_raw};
use crate::{
    error::{Errno, Result},
    header::{
        errno::{EAFNOSUPPORT, EINVAL},
        sys_socket::{
            constants::{AF_UNIX, SOCK_CLOEXEC, SOCK_NONBLOCK},
            msghdr, sockaddr, socklen_t,
        },
        sys_un::sockaddr_un,
    },
    platform::{PalSocket, types::*},
};

fn unix_socket_path(address: *const sockaddr, address_len: socklen_t) -> Result<CString> {
    if address.is_null() {
        return Err(Errno(EINVAL));
    }

    let address = unsafe { &*address.cast::<sockaddr_un>() };
    if address.sun_family as c_int != AF_UNIX {
        return Err(Errno(EAFNOSUPPORT));
    }

    let path_offset = address.path_offset();
    let len = address_len as usize;
    if len <= path_offset {
        return Err(Errno(EINVAL));
    }

    let path_len = len.saturating_sub(path_offset).min(address.sun_path.len());
    let path_bytes =
        unsafe { slice::from_raw_parts(address.sun_path.as_ptr().cast::<u8>(), path_len) };
    let end = path_bytes
        .iter()
        .position(|&byte| byte == 0)
        .unwrap_or(path_len);
    if end == 0 || path_bytes.first() == Some(&0) {
        return Err(Errno(EINVAL));
    }

    CString::new(&path_bytes[..end]).map_err(|_| Errno(EINVAL))
}

fn apply_socket_flags(socket: c_int, kind: c_int) -> Result<()> {
    if (kind & SOCK_NONBLOCK) != 0 {
        e_raw(process_result(control_object(
            socket as u64,
            ControlCommand::SetFlags,
            ObjectFlags::NONBLOCK.bits(),
        )))?;
    }

    Ok(())
}

impl PalSocket for Sys {
    unsafe fn accept(
        socket: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<c_int> {
        let accepted = e_raw(process_result(socket_accept(socket as u64)))? as c_int;

        if !address_len.is_null() {
            unsafe {
                *address_len = 0;
            }
        }
        let _ = address;

        Ok(accepted)
    }

    unsafe fn bind(socket: c_int, address: *const sockaddr, address_len: socklen_t) -> Result<()> {
        let path = unix_socket_path(address, address_len)?;
        e_raw(process_result(socket_bind(socket as u64, path.as_ptr()))).map(|_| ())
    }

    unsafe fn connect(
        socket: c_int,
        address: *const sockaddr,
        address_len: socklen_t,
    ) -> Result<c_int> {
        let path = unix_socket_path(address, address_len)?;
        e_raw(process_result(socket_connect(socket as u64, path.as_ptr())))
            .map(|value| value as c_int)
    }

    unsafe fn getpeername(
        socket: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<()> {
        let _ = (socket, address, address_len);
        Sys::stub("GETPEERNAME").map(|_| ())
    }

    unsafe fn getsockname(
        socket: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<()> {
        let _ = (socket, address, address_len);
        Sys::stub("GETSOCKNAME").map(|_| ())
    }

    unsafe fn getsockopt(
        socket: c_int,
        level: c_int,
        option_name: c_int,
        option_value: *mut c_void,
        option_len: *mut socklen_t,
    ) -> Result<()> {
        let _ = (socket, level, option_name, option_value, option_len);
        Sys::stub("GETSOCKOPT").map(|_| ())
    }

    fn listen(socket: c_int, backlog: c_int) -> Result<()> {
        let backlog = backlog.max(0) as u64;
        e_raw(process_result(socket_listen(socket as u64, backlog))).map(|_| ())
    }

    unsafe fn recvfrom(
        socket: c_int,
        buf: *mut c_void,
        len: size_t,
        flags: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<usize> {
        let _ = (socket, buf, len, flags, address, address_len);
        Sys::stub("RECVFROM")
    }

    unsafe fn recvmsg(socket: c_int, msg: *mut msghdr, flags: c_int) -> Result<usize> {
        let _ = (socket, msg, flags);
        Sys::stub("RECVMSG")
    }

    unsafe fn sendmsg(socket: c_int, msg: *const msghdr, flags: c_int) -> Result<usize> {
        let _ = (socket, msg, flags);
        Sys::stub("SENDMSG")
    }

    unsafe fn sendto(
        socket: c_int,
        buf: *const c_void,
        len: size_t,
        flags: c_int,
        dest_addr: *const sockaddr,
        dest_len: socklen_t,
    ) -> Result<usize> {
        let _ = (socket, buf, len, flags, dest_addr, dest_len);
        Sys::stub("SENDTO")
    }

    unsafe fn setsockopt(
        socket: c_int,
        level: c_int,
        option_name: c_int,
        option_value: *const c_void,
        option_len: socklen_t,
    ) -> Result<()> {
        let _ = (socket, level, option_name, option_value, option_len);
        Sys::stub("SETSOCKOPT").map(|_| ())
    }

    fn shutdown(socket: c_int, how: c_int) -> Result<()> {
        let _ = (socket, how);
        Sys::stub("SHUTDOWN").map(|_| ())
    }

    unsafe fn socket(domain: c_int, kind: c_int, protocol: c_int) -> Result<c_int> {
        let base_kind = kind & !(SOCK_NONBLOCK | SOCK_CLOEXEC);
        let socket = e_raw(process_result(create_socket(
            domain as u64,
            base_kind as u64,
            protocol as u64,
        )))? as c_int;

        apply_socket_flags(socket, kind)?;

        Ok(socket)
    }

    fn socketpair(domain: c_int, kind: c_int, protocol: c_int, sv: &mut [c_int; 2]) -> Result<()> {
        let _ = (domain, kind, protocol, sv);
        Sys::stub("SOCKETPAIR").map(|_| ())
    }
}
