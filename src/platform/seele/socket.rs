use super::Sys;
use crate::{
    error::Result,
    header::sys_socket::{msghdr, sockaddr, socklen_t},
    platform::{PalSocket, types::*},
};

impl PalSocket for Sys {
    unsafe fn accept(
        socket: c_int,
        address: *mut sockaddr,
        address_len: *mut socklen_t,
    ) -> Result<c_int> {
        let _ = (socket, address, address_len);
        Ok(Sys::stub("ACCEPT")? as c_int)
    }

    unsafe fn bind(socket: c_int, address: *const sockaddr, address_len: socklen_t) -> Result<()> {
        let _ = (socket, address, address_len);
        Sys::stub("BIND").map(|_| ())
    }

    unsafe fn connect(
        socket: c_int,
        address: *const sockaddr,
        address_len: socklen_t,
    ) -> Result<c_int> {
        let _ = (socket, address, address_len);
        Ok(Sys::stub("CONNECT")? as c_int)
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
        let _ = (socket, backlog);
        Sys::stub("LISTEN").map(|_| ())
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
        let _ = (domain, kind, protocol);
        Ok(Sys::stub("SOCKET")? as c_int)
    }

    fn socketpair(domain: c_int, kind: c_int, protocol: c_int, sv: &mut [c_int; 2]) -> Result<()> {
        let _ = (domain, kind, protocol, sv);
        Sys::stub("SOCKETPAIR").map(|_| ())
    }
}
