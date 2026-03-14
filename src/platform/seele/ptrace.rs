use super::{
    super::{PalPtrace, types::*},
    Sys,
};
use crate::error::Result;

impl PalPtrace for Sys {
    unsafe fn ptrace(
        request: c_int,
        pid: pid_t,
        addr: *mut c_void,
        data: *mut c_void,
    ) -> Result<c_int> {
        let _ = (request, pid, addr, data);
        Ok(Sys::stub("PTRACE")? as c_int)
    }
}
