//! Dynamic loading and linking.

// FIXME(andypython): remove this when #![allow(warnings, unused_variables)] is
// dropped from src/lib.rs.
#![warn(warnings, unused_variables)]

use core::{mem, ptr};
use elysia_os_lib::syscalls;
use object::{
    Endianness,
    elf::{self, ProgramHeader32, ProgramHeader64},
    read::elf::ProgramHeader,
};

use self::tcb::{Master, Tcb};
use crate::{
    header::sys_auxv::AT_NULL,
    platform::{Pal, Sys},
    start::Stack,
};

pub const PATH_SEP: char = ':';

mod access;
pub mod callbacks;
pub mod debug;
mod dso;
pub mod linker;
pub mod start;
pub mod tcb;

pub use generic_rt::{ExpectTlsFree, panic_notls};

static mut STATIC_TCB_MASTER: Master = Master {
    ptr: ptr::null_mut(),
    image_size: 0,
    segment_size: 0,
    offset: 0,
};

#[inline(never)]
pub fn static_init(
    sp: &'static Stack,
    #[cfg(target_os = "redox")] thr_fd: redox_rt::proc::FdGuardUpper,
) {
    syscalls::print("static init startz").unwrap();
    let fmt = format!("{:?}", sp.argc);
    syscalls::print(&fmt).unwrap();
    const SIZEOF_PHDR64: usize = mem::size_of::<ProgramHeader64<Endianness>>();
    const SIZEOF_PHDR32: usize = mem::size_of::<ProgramHeader32<Endianness>>();

    let mut phdr_opt = None;
    let mut phent_opt = None;
    let mut phnum_opt = None;

    syscalls::print("sp.auxv()").unwrap();
    let mut auxv = sp.auxv();
    syscalls::print(format!("{:?}", unsafe { *auxv }).as_str()).unwrap();
    syscalls::print("sp.auxv() done").unwrap();
    loop {
        let (kind, value) = unsafe { *auxv };
        if kind == AT_NULL {
            break;
        }

        match kind {
            3 => phdr_opt = Some(value),
            4 => phent_opt = Some(value),
            5 => phnum_opt = Some(value),
            _ => (),
        }

        auxv = unsafe { auxv.add(1) };
    }
    syscalls::print("auxv thingy done").unwrap();

    let phdr = phdr_opt.expect_notls("failed to find AT_PHDR");
    let phent = phent_opt.expect_notls("failed to find AT_PHENT");
    let phnum = phnum_opt.expect_notls("failed to find AT_PHNUM");

    syscalls::print("Static init 1").unwrap();

    for i in 0..phnum {
        let ph_addr = phdr + phent * i;
        let endian = Endianness::default();
        let (p_align, p_filesz, p_memsz, p_type, p_vaddr) = match phent {
            SIZEOF_PHDR64 => unsafe {
                let ph = &*(ph_addr as *const ProgramHeader64<Endianness>);
                (
                    ph.p_align(endian) as usize,
                    ph.p_filesz(endian) as usize,
                    ph.p_memsz(endian) as usize,
                    ph.p_type(endian),
                    ph.p_vaddr(endian) as usize,
                )
            },

            SIZEOF_PHDR32 => unsafe {
                let ph = &*(ph_addr as *const ProgramHeader32<Endianness>);
                (
                    ph.p_align(endian) as usize,
                    ph.p_filesz(endian) as usize,
                    ph.p_memsz(endian) as usize,
                    ph.p_type(endian),
                    ph.p_vaddr(endian) as usize,
                )
            },
            _ => panic_notls(format_args!("unknown AT_PHENT size {}", phent)),
        };

        syscalls::print("Static init 2").unwrap();

        let page_size = Sys::getpagesize();
        let voff = p_vaddr % page_size;
        // let vaddr = ph.p_vaddr as usize - voff;
        let vsize = ((p_memsz + voff + page_size - 1) / page_size) * page_size;

        if p_type == elf::PT_TLS {
            let valign = if p_align > 0 {
                ((p_memsz + (p_align - 1)) / p_align) * p_align
            } else {
                p_memsz
            };

            syscalls::print("static init 3").unwrap();

            unsafe {
                STATIC_TCB_MASTER.ptr = p_vaddr as *const u8;
                STATIC_TCB_MASTER.image_size = p_filesz;
                STATIC_TCB_MASTER.offset = valign;

                let tcb = Tcb::new(vsize).expect_notls("failed to allocate TCB");
                tcb.masters_ptr = ptr::addr_of_mut!(STATIC_TCB_MASTER);
                tcb.masters_len = mem::size_of::<Master>();
                tcb.copy_masters()
                    .expect_notls("failed to copy TLS master data");
                tcb.activate(
                    #[cfg(target_os = "redox")]
                    Some(thr_fd),
                );
            }

            //TODO: Warning on multiple TLS sections?
            return;
        }
    }
}

#[cfg(any(target_os = "linux", target_os = "redox"))]
pub unsafe fn init(
    sp: &'static Stack,
    #[cfg(target_os = "redox")] thr_fd: redox_rt::proc::FdGuardUpper,
) {
    let tp: usize;

    {
        use alloc::string::ToString;
        use elysia_os_lib::syscalls::{self, get_fs};

        syscalls::print("get fs").unwrap();
        tp = get_fs().unwrap();
        syscalls::print(tp.to_string().as_str()).unwrap();
    }
    #[cfg(target_arch = "aarch64")]
    unsafe {
        core::arch::asm!(
            "mrs {}, tpidr_el0",
            out(reg) tp,
        );
    }
    #[cfg(all(target_os = "redox", target_arch = "x86"))]
    {
        let mut env = syscall::EnvRegisters::default();

        {
            let file = thr_fd
                .dup(b"regs/env")
                .expect_notls("failed to open handle for process registers");

            file.read(&mut env).expect_notls("failed to read gsbase");
        }

        tp = env.gsbase as usize;
    }
    #[cfg(all(target_os = "redox", target_arch = "x86_64"))]
    {
        let mut env = syscall::EnvRegisters::default();

        {
            let file = thr_fd
                .dup(b"regs/env")
                .expect_notls("failed to open handle for process registers");

            file.read(&mut env).expect_notls("failed to read fsbase");
        }

        tp = env.fsbase as usize;
    }
    #[cfg(all(target_os = "redox", target_arch = "riscv64"))]
    unsafe {
        core::arch::asm!(
            "mv {}, tp",
            out(reg) tp,
        );
    }

    if tp == 0 {
        use elysia_os_lib::syscalls;

        syscalls::print("Static init").unwrap();
        static_init(
            sp,
            #[cfg(target_os = "redox")]
            thr_fd,
        );
        syscalls::print("Static init done").unwrap();
    } else {
        // The thread fd must already be present in the already existing TCB. Don't close it.
        #[cfg(target_os = "redox")]
        core::mem::forget(thr_fd);
    }
}

pub unsafe fn fini() {
    if let Some(tcb) = unsafe { Tcb::current() } {
        if !tcb.linker_ptr.is_null() {
            let linker = unsafe { (*tcb.linker_ptr).lock() };
            linker.fini();
        }
    }
}
