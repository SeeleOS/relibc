use core::ffi::c_void;

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetIP(_ctx: *mut c_void) -> usize {
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_Backtrace(
    _cb: extern "C" fn(*mut c_void, *mut c_void) -> i32,
    _data: *mut c_void,
) -> i32 {
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetTextRelBase(_ctx: *mut c_void) -> usize {
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetDataRelBase(_ctx: *mut c_void) -> usize {
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetLanguageSpecificData(_ctx: *mut c_void) -> *const c_void {
    core::ptr::null()
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetIPInfo(_ctx: *mut c_void, ip_before_insn: *mut i32) -> usize {
    if !ip_before_insn.is_null() {
        unsafe {
            *ip_before_insn = 0;
        }
    }
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_GetRegionStart(_ctx: *mut c_void) -> usize {
    0
}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_SetGR(_ctx: *mut c_void, _index: i32, _value: usize) {}

#[cfg(not(test))]
#[allow(non_snake_case)]
#[linkage = "weak"]
#[unsafe(no_mangle)]
pub extern "C" fn _Unwind_SetIP(_ctx: *mut c_void, _value: usize) {}
