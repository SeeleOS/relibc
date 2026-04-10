use alloc::{ffi::CString, format};
use core::{
    slice,
    sync::atomic::{AtomicU64, Ordering},
};

use seele_sys::{
    abi::object::{ControlCommand, ObjectFlags},
    syscalls::{
        filesystem::delete_file,
        object::{control_object, read_object, write_object},
        socket::{
            accept as socket_accept, bind as socket_bind, connect as socket_connect,
            getpeername as socket_getpeername, getsockname as socket_getsockname,
            getsockopt as socket_getsockopt, listen as socket_listen, recvmsg as socket_recvmsg,
            shutdown as socket_shutdown, socket as create_socket,
        },
    },
    utils::process_result,
};

use super::{Sys, e_raw};
use crate::{
    error::{Errno, Result},
    header::{
        bits_iovec::iovec,
        errno::{EAFNOSUPPORT, EINVAL},
        sys_socket::{
            constants::{AF_UNIX, SOCK_CLOEXEC, SOCK_NONBLOCK, SOCK_STREAM},
            msghdr, sockaddr,
        },
        sys_un::sockaddr_un,
    },
    platform::{Pal, PalSocket, types::*},
};
pub type socklen_t = u32;
static SOCKETPAIR_COUNTER: AtomicU64 = AtomicU64::new(0);

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

fn next_socketpair_path() -> Result<CString> {
    let pid = Sys::getpid();
    let tid = Sys::gettid();
    let seq = SOCKETPAIR_COUNTER.fetch_add(1, Ordering::Relaxed);
    CString::new(format!("/tmp/.relibc-pipe-{}-{}-{}", pid, tid, seq)).map_err(|_| Errno(EINVAL))
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
        let result = e_raw(process_result(socket_bind(socket as u64, path.as_ptr()))).map(|_| ());
        if let Err(ref err) = result {
            Sys::print_stub_message(format_args!(
                "seele bind failed: fd={} path={} errno={}\n",
                socket,
                path.as_c_str().to_str().unwrap_or("<invalid>"),
                err.0
            ));
        }
        result
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
        e_raw(process_result(socket_getpeername(
            socket as u64,
            address.cast::<u8>(),
            address_len,
        )))?;
        Ok(())
    }

    unsafe fn getsockname(
        socket: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<()> {
        e_raw(process_result(socket_getsockname(
            socket as u64,
            address.cast::<u8>(),
            address_len,
        )))?;
        Ok(())
    }

    unsafe fn getsockopt(
        socket: c_int,
        level: c_int,
        option_name: c_int,
        option_value: *mut c_void,
        option_len: *mut socklen_t,
    ) -> Result<()> {
        e_raw(process_result(socket_getsockopt(
            socket as u64,
            level as u64,
            option_name as u64,
            option_value.cast::<u8>(),
            option_len,
        )))?;
        Ok(())
    }

    fn listen(socket: c_int, backlog: c_int) -> Result<()> {
        let backlog = backlog.max(0) as u64;
        let result = e_raw(process_result(socket_listen(socket as u64, backlog))).map(|_| ());
        if let Err(ref err) = result {
            Sys::print_stub_message(format_args!(
                "seele listen failed: fd={} backlog={} errno={}\n",
                socket, backlog, err.0
            ));
        }
        result
    }

    unsafe fn recvfrom(
        socket: c_int,
        buf: *mut c_void,
        len: size_t,
        flags: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<usize> {
        let _ = flags;

        if !address_len.is_null() {
            unsafe {
                *address_len = 0;
            }
        }
        let _ = address;

        let buffer = unsafe { slice::from_raw_parts_mut(buf.cast::<u8>(), len) };
        e_raw(process_result(read_object(socket as u64, buffer)))
    }

    unsafe fn recvmsg(socket: c_int, msg: *mut msghdr, flags: c_int) -> Result<usize> {
        e_raw(process_result(socket_recvmsg(
            socket as u64,
            msg.cast::<u8>(),
            flags as u64,
        )))
    }

    unsafe fn sendmsg(socket: c_int, msg: *const msghdr, flags: c_int) -> Result<usize> {
        let _ = flags;

        if msg.is_null() {
            return Err(Errno(EINVAL));
        }

        let msg = unsafe { &*msg };
        if !msg.msg_name.is_null()
            || msg.msg_namelen != 0
            || !msg.msg_control.is_null()
            || msg.msg_controllen != 0
        {
            return Err(Errno(EINVAL));
        }

        if msg.msg_iovlen == 0 {
            return Ok(0);
        }
        if msg.msg_iov.is_null() {
            return Err(Errno(EINVAL));
        }

        let iovs = unsafe { slice::from_raw_parts(msg.msg_iov.cast::<iovec>(), msg.msg_iovlen) };
        let mut total_written = 0usize;

        for iov in iovs {
            if iov.iov_len == 0 {
                continue;
            }
            if iov.iov_base.is_null() {
                return Err(Errno(EINVAL));
            }

            let buffer = unsafe { slice::from_raw_parts(iov.iov_base.cast::<u8>(), iov.iov_len) };
            let written = e_raw(process_result(write_object(socket as u64, buffer)))?;
            total_written += written;

            if written < buffer.len() {
                break;
            }
        }

        Ok(total_written)
    }

    unsafe fn sendto(
        socket: c_int,
        buf: *const c_void,
        len: size_t,
        flags: c_int,
        dest_addr: *const sockaddr,
        dest_len: socklen_t,
    ) -> Result<usize> {
        let _ = flags;
        if !dest_addr.is_null() || dest_len != 0 {
            return Err(Errno(EINVAL));
        }

        let buffer = unsafe { slice::from_raw_parts(buf.cast::<u8>(), len) };
        e_raw(process_result(write_object(socket as u64, buffer)))
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
        e_raw(process_result(socket_shutdown(socket as u64, how as u64)))?;
        Ok(())
    }

    unsafe fn socket(domain: c_int, kind: c_int, protocol: c_int) -> Result<c_int> {
        let base_kind = kind & !(SOCK_NONBLOCK | SOCK_CLOEXEC);
        let result = e_raw(process_result(create_socket(
            domain as u64,
            base_kind as u64,
            protocol as u64,
        )));
        let socket = match result {
            Ok(fd) => fd as c_int,
            Err(err) => {
                Sys::print_stub_message(format_args!(
                    "seele socket failed: domain={} kind=0x{:x} base_kind=0x{:x} protocol={} errno={}\n",
                    domain, kind, base_kind, protocol, err.0
                ));
                return Err(err);
            }
        };

        apply_socket_flags(socket, kind)?;

        Ok(socket)
    }

    fn socketpair(domain: c_int, kind: c_int, protocol: c_int, sv: &mut [c_int; 2]) -> Result<()> {
        let base_kind = kind & !(SOCK_NONBLOCK | SOCK_CLOEXEC);
        if domain != AF_UNIX || base_kind != SOCK_STREAM || protocol != 0 {
            return Err(Errno(EINVAL));
        }

        let path = next_socketpair_path()?;
        sv[0] = -1;
        sv[1] = -1;

        let listener = match e_raw(process_result(create_socket(
            domain as u64,
            base_kind as u64,
            protocol as u64,
        ))) {
            Ok(fd) => fd as c_int,
            Err(err) => return Err(err),
        };

        let result = (|| {
            e_raw(process_result(socket_bind(listener as u64, path.as_ptr())))?;
            e_raw(process_result(socket_listen(listener as u64, 1)))?;

            let first = e_raw(process_result(create_socket(
                domain as u64,
                base_kind as u64,
                protocol as u64,
            )))? as c_int;
            if let Err(err) = e_raw(process_result(socket_connect(first as u64, path.as_ptr()))) {
                let _ = Sys::close(first);
                return Err(err);
            }
            let second = match e_raw(process_result(socket_accept(listener as u64))) {
                Ok(fd) => fd as c_int,
                Err(err) => {
                    let _ = Sys::close(first);
                    return Err(err);
                }
            };

            if let Err(err) = apply_socket_flags(first, kind) {
                let _ = Sys::close(first);
                let _ = Sys::close(second);
                return Err(err);
            }
            if let Err(err) = apply_socket_flags(second, kind) {
                let _ = Sys::close(first);
                let _ = Sys::close(second);
                return Err(err);
            }

            sv[0] = first;
            sv[1] = second;
            Ok(())
        })();

        if result.is_err() {
            if sv[0] >= 0 {
                let _ = Sys::close(sv[0]);
                sv[0] = -1;
            }
            if sv[1] >= 0 {
                let _ = Sys::close(sv[1]);
                sv[1] = -1;
            }
        }
        let _ = e_raw(process_result(delete_file(path.as_ptr())));
        let _ = Sys::close(listener);
        result
    }
}
