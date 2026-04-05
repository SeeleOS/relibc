use alloc::{slice, str};
use seele_sys::{
    abi::{
        framebuffer::{FramebufferInfo as SeeleFramebufferInfo, FramebufferPixelFormat},
        object::{ControlCommand, TerminalInfo as SeeleTerminalInfo, device_from_path},
    },
    misc::SystemInfo,
    permission::Permissions,
    syscalls::{
        self, allocate_mem, deallocate_mem, execve,
        filesystem::{
            change_dir, create_directory, delete_file, directory_contents, file_info,
            get_current_directory, link_file, open_file,
        },
        futex, get_process_id, get_process_parent_id, get_system_info, get_thread_id,
        misc::{get_current_time, sleep, time_since_boot},
        object::{
            clone_object, clone_object_to, configurate_object, control_object,
            get_framebuffer_info, get_terminal_info, mmap_object, open_device, read_object,
            remove_object, set_terminal_info, write_object,
        },
        update_mem_perms, wait_for_process_exit,
    },
    utils::process_result,
};
use spin::Mutex;

use super::{Pal, types::*};
use crate::{
    c_str::CStr,
    header::{
        dirent::dirent,
        errno::{EAGAIN, EEXIST, EINVAL, EIO, ENOSYS},
        fcntl::{AT_EMPTY_PATH, AT_FDCWD, AT_REMOVEDIR, O_CREAT, O_EXCL, sys},
        signal::{SIG_BLOCK, SIG_SETMASK, SIG_UNBLOCK, SIGCHLD, sigevent, sigset_t},
        sys_ioctl::{
            FB_TYPE_PACKED_PIXELS, FB_VISUAL_TRUECOLOR, FBIOGET_FSCREENINFO, FBIOGET_VSCREENINFO,
            TCGETS, TCSETS, TCSETSF, TCSETSW, TIOCGWINSZ, fb_bitfield, fb_fix_screeninfo,
            fb_var_screeninfo, winsize,
        },
        sys_mman::{
            MAP_ANON, MAP_FIXED, MAP_FIXED_NOREPLACE, MAP_PRIVATE, MAP_STACK, MAP_TYPE, PROT_EXEC,
            PROT_NONE, PROT_READ, PROT_WRITE,
        },
        sys_resource::{rlimit, rusage},
        sys_select::timeval,
        sys_stat::{S_IFIFO, stat},
        sys_statvfs::statvfs,
        sys_time::timezone,
        termios::{ECHO, ECHOE, ECHOK, ECHONL, ICANON, termios},
        time::{CLOCK_MONOTONIC, CLOCK_REALTIME, itimerspec},
        unistd::{F_OK, R_OK, SEEK_CUR, SEEK_SET, W_OK, X_OK, getpid},
    },
    ld_so::tcb::OsSpecific,
    out::Out,
    pthread::set_cancel_state,
};
use core::{
    num::NonZeroU64,
    ptr,
    str::from_utf8,
    sync::atomic::{AtomicU64, Ordering},
};
// use header::sys_times::tms;
use crate::{
    error::{Errno, Result},
    header::{bits_time::timespec, sys_utsname::utsname},
};

mod epoll;
mod ptrace;
mod signal;
mod socket;
mod unwind_stub;

pub use unwind_stub::*;

const SYS_CLONE: usize = 56;
const CLONE_VM: usize = 0x0100;
const CLONE_FS: usize = 0x0200;
const CLONE_FILES: usize = 0x0400;
const CLONE_SIGHAND: usize = 0x0800;
const CLONE_THREAD: usize = 0x00010000;
const PRINT_STUB_MESSAGE: bool = true;
static SIGPROCMASK_STATE: AtomicU64 = AtomicU64::new(0);

fn prot_to_permissions(prot: c_int) -> Permissions {
    let mut permissions = Permissions::empty();

    if (prot & PROT_READ) != 0 {
        permissions |= Permissions::READABLE;
    }
    if (prot & PROT_WRITE) != 0 {
        permissions |= Permissions::WRITABLE;
    }
    if (prot & PROT_EXEC) != 0 {
        permissions |= Permissions::EXECUTABLE;
    }

    permissions
}

#[repr(C)]
#[derive(Default)]
struct linux_statfs {
    f_type: c_long,       /* type of file system (see below) */
    f_bsize: c_long,      /* optimal transfer block size */
    f_blocks: fsblkcnt_t, /* total data blocks in file system */
    f_bfree: fsblkcnt_t,  /* free blocks in fs */
    f_bavail: fsblkcnt_t, /* free blocks available to unprivileged user */
    f_files: fsfilcnt_t,  /* total file nodes in file system */
    f_ffree: fsfilcnt_t,  /* free file nodes in fs */
    f_fsid: c_long,       /* file system id */
    f_namelen: c_long,    /* maximum length of filenames */
    f_frsize: c_long,     /* fragment size (since Linux 2.6) */
    f_flags: c_long,
    f_spare: [c_long; 4],
}

// TODO
const ERRNO_MAX: usize = 4095;

pub fn e_raw(sys: usize) -> Result<usize> {
    if sys > ERRNO_MAX.wrapping_neg() {
        Err(Errno(sys.wrapping_neg() as _))
    } else {
        Ok(sys)
    }
}

/// Linux syscall implementation of the platform abstraction layer.
pub struct Sys;

impl Sys {
    fn framebuffer_bitfields(
        pixel_format: FramebufferPixelFormat,
    ) -> (fb_bitfield, fb_bitfield, fb_bitfield) {
        match pixel_format {
            // Seele stores pixels in memory as RGB or BGR byte order.
            FramebufferPixelFormat::Rgb => (
                fb_bitfield {
                    offset: 0,
                    length: 8,
                    msb_right: 0,
                },
                fb_bitfield {
                    offset: 8,
                    length: 8,
                    msb_right: 0,
                },
                fb_bitfield {
                    offset: 16,
                    length: 8,
                    msb_right: 0,
                },
            ),
            FramebufferPixelFormat::Bgr => (
                fb_bitfield {
                    offset: 16,
                    length: 8,
                    msb_right: 0,
                },
                fb_bitfield {
                    offset: 8,
                    length: 8,
                    msb_right: 0,
                },
                fb_bitfield {
                    offset: 0,
                    length: 8,
                    msb_right: 0,
                },
            ),
        }
    }

    fn fill_linux_fb_fix(info: SeeleFramebufferInfo, out: &mut fb_fix_screeninfo) {
        *out = fb_fix_screeninfo::default();
        let id = b"seelefb\0";
        for (dst, src) in out.id.iter_mut().zip(id.iter().copied()) {
            *dst = src as c_char;
        }
        out.smem_len = info.byte_len as c_uint;
        out.type_ = FB_TYPE_PACKED_PIXELS as c_uint;
        out.visual = FB_VISUAL_TRUECOLOR as c_uint;
        out.line_length = (info.stride * info.bytes_per_pixel) as c_uint;
    }

    fn fill_linux_fb_var(info: SeeleFramebufferInfo, out: &mut fb_var_screeninfo) {
        *out = fb_var_screeninfo::default();
        out.xres = info.width as c_uint;
        out.yres = info.height as c_uint;
        out.xres_virtual = info.stride as c_uint;
        out.yres_virtual = info.height as c_uint;
        out.bits_per_pixel = (info.bytes_per_pixel * 8) as c_uint;
        let (red, green, blue) = Self::framebuffer_bitfields(info.pixel_format);
        out.red = red;
        out.green = green;
        out.blue = blue;
        out.transp = fb_bitfield::default();
        out.height = info.height as c_uint;
        out.width = info.width as c_uint;
    }

    fn print_stub_message(args: core::fmt::Arguments<'_>) {
        use core::fmt::Write;

        if !PRINT_STUB_MESSAGE {
            return;
        }

        let mut w = super::FileWriter::new(2);
        let _ = w.write_fmt(args);
    }

    /// Stub for unimplemented Linux-style syscalls on Seele.
    /// Prints a message and returns Ok(0) to indicate a no-op success.
    pub(crate) fn stub(name: &str) -> Result<usize> {
        Self::print_stub_message(format_args!("unimplemented systemcall {name}\n"));
        Err(Errno(38))
    }

    pub unsafe fn ioctl(fd: c_int, request: c_ulong, out: *mut c_void) -> Result<c_int> {
        match request {
            FBIOGET_FSCREENINFO => {
                if out.is_null() {
                    return Err(Errno(EINVAL));
                }
                let mut info = SeeleFramebufferInfo::default();
                e_raw(process_result(get_framebuffer_info(fd as u64, &mut info)))?;
                Self::fill_linux_fb_fix(info, unsafe { &mut *out.cast::<fb_fix_screeninfo>() });
                Ok(0)
            }
            FBIOGET_VSCREENINFO => {
                if out.is_null() {
                    return Err(Errno(EINVAL));
                }
                let mut info = SeeleFramebufferInfo::default();
                e_raw(process_result(get_framebuffer_info(fd as u64, &mut info)))?;
                Self::fill_linux_fb_var(info, unsafe { &mut *out.cast::<fb_var_screeninfo>() });
                Ok(0)
            }
            TCGETS => {
                // Makes a new blank Seele terminal info
                let mut info = SeeleTerminalInfo::default();
                // Writes the actual seele terminal info to it
                e_raw(process_result(get_terminal_info(fd as u64, &mut info)))?;

                if !out.is_null() {
                    // Updates the termios with the seele term info
                    *(unsafe { &mut *out.cast::<termios>() }) = termios::from(info);
                }

                Ok(0)
            }
            TCSETS | TCSETSW | TCSETSF => {
                if out.is_null() {
                    return Err(Errno(EINVAL));
                }

                // Gets the current terminal info
                let mut current = SeeleTerminalInfo::default();
                e_raw(process_result(get_terminal_info(fd as u64, &mut current)))?;

                // Casts the termios as seele terminal info
                let new_info = (unsafe { &*out.cast::<termios>() }).as_seele_terminal_info(current);
                // Sets the terminal info as the termios (changed to seele terminal info)
                e_raw(process_result(set_terminal_info(fd as u64, &new_info)))?;
                Ok(0)
            }
            TIOCGWINSZ => {
                let mut info = SeeleTerminalInfo::default();
                e_raw(process_result(get_terminal_info(fd as u64, &mut info)))?;

                if !out.is_null() {
                    let out = unsafe { &mut *out.cast::<winsize>() };
                    out.ws_row = info.rows as u16;
                    out.ws_col = info.cols as u16;
                    out.ws_xpixel = 0;
                    out.ws_ypixel = 0;
                }

                Ok(0)
            }
            TIOCSWINSZ => {
                if out.is_null() {
                    return Err(Errno(EINVAL));
                }

                let size = unsafe { &*out.cast::<winsize>() };
                let mut info = SeeleTerminalInfo::default();
                e_raw(process_result(get_terminal_info(fd as u64, &mut info)))?;

                info.rows = u64::from(size.ws_row);
                info.cols = u64::from(size.ws_col);
                e_raw(process_result(set_terminal_info(fd as u64, &info)))?;

                Ok(0)
            }
            _ => e_raw(process_result(configurate_object(
                fd as u64,
                request,
                out as *mut u8,
            )))
            .map(|i| i as c_int),
        }
    }

    // fn times(out: *mut tms) -> clock_t {
    //     unsafe { syscall!(TIMES, out) as clock_t }
    // }
    //

    pub(crate) fn sigprocmask_stub(
        how: c_int,
        set: Option<&sigset_t>,
        oset: Option<&mut sigset_t>,
    ) -> Result<()> {
        let old = SIGPROCMASK_STATE.load(Ordering::SeqCst);

        if let Some(oset) = oset {
            *oset = old;
        }

        let Some(set) = set else {
            return Ok(());
        };

        let new = match how {
            SIG_BLOCK => old | *set,
            SIG_UNBLOCK => old & !*set,
            SIG_SETMASK => *set,
            _ => return Err(Errno(EINVAL)),
        };

        Self::print_stub_message(format_args!(
            "stub RT_SIGPROCMASK how={how} old=0x{old:016x} set=0x{set:016x} new=0x{new:016x}\n"
        ));

        SIGPROCMASK_STATE.store(new, Ordering::SeqCst);
        Ok(())
    }
}

impl Pal for Sys {
    #[cfg(any(target_arch = "x86_64", target_arch = "x86"))]
    fn access(path: CStr, mode: c_int) -> Result<()> {
        let supported_mode_bits = R_OK | W_OK | X_OK;
        if (mode & !supported_mode_bits) != F_OK {
            return Err(Errno(EINVAL));
        }
        if mode != F_OK {
            return Err(Errno(ENOSYS));
        }

        let mut stat = stat::default();
        let from_current_dir = !path.to_bytes().starts_with(b"/");

        e_raw(process_result(file_info(
            from_current_dir,
            false,
            path.as_ptr(),
            &mut stat as *mut stat as *mut u8,
            0,
        )))
        .map(|_| ())
    }

    fn openat(dirfd: c_int, path: CStr, oflag: c_int, mode: mode_t) -> Result<c_int> {
        Sys::stub("OPENAT").map(|a| a as c_int)
    }

    #[cfg(target_arch = "aarch64")]
    fn access(path: CStr, mode: c_int) -> Result<()> {
        let _ = (path, mode);
        Sys::stub("FACCESSAT").map(|_| ())
    }

    unsafe fn brk(addr: *mut c_void) -> Result<*mut c_void> {
        let _ = addr;
        Ok(Sys::stub("BRK")? as *mut c_void)
    }

    fn chdir(path: CStr) -> Result<()> {
        change_dir(path.as_ptr(), path.len() as u64);
        Ok(())
    }

    fn chmod(path: CStr, mode: mode_t) -> Result<()> {
        let _ = (path, mode);
        Ok(())
    }

    fn chown(path: CStr, owner: uid_t, group: gid_t) -> Result<()> {
        let _ = (path, owner, group);
        Sys::stub("FCHOWNAT").map(|_| ())
    }

    fn clock_getres(clk_id: clockid_t, res: Option<Out<timespec>>) -> Result<()> {
        let _ = (clk_id, res);
        Sys::stub("CLOCK_GETRES").map(|_| ())
    }

    fn clock_gettime(clk_id: clockid_t, mut tp: Out<timespec>) -> Result<()> {
        let nanoseconds = match clk_id {
            CLOCK_REALTIME => e_raw(process_result(get_current_time()))?,
            CLOCK_MONOTONIC => e_raw(process_result(time_since_boot()))?,
            _ => return Err(Errno(EINVAL)),
        } as i64;

        unsafe {
            let ts = tp.as_mut_ptr();
            (*ts).tv_sec = nanoseconds / 1_000_000_000;
            (*ts).tv_nsec = nanoseconds % 1_000_000_000;
        }

        Ok(())
    }

    unsafe fn clock_settime(clk_id: clockid_t, tp: *const timespec) -> Result<()> {
        Err(Errno(ENOSYS))
    }

    fn close(fildes: c_int) -> Result<()> {
        e_raw(process_result(remove_object(fildes as u64))).map(|_| ())
    }

    fn dup(fildes: c_int) -> Result<c_int> {
        e_raw(process_result(clone_object(fildes as u64))).map(|f| f as c_int)
    }

    fn dup2(fildes: c_int, fildes2: c_int) -> Result<c_int> {
        e_raw(process_result(clone_object_to(
            fildes as u64,
            fildes2 as u64,
        )))
        .map(|f| f as c_int)
    }

    unsafe fn execve(path: CStr, argv: *const *mut c_char, envp: *const *mut c_char) -> Result<()> {
        unsafe {
            e_raw(process_result(execve(
                from_utf8(slice::from_raw_parts(
                    path.as_ptr() as *const u8,
                    path.len(),
                ))
                .unwrap(),
                argv,
                envp,
            )))?
        };
        unreachable!()
    }
    unsafe fn fexecve(
        fildes: c_int,
        argv: *const *mut c_char,
        envp: *const *mut c_char,
    ) -> Result<()> {
        let _ = (fildes, argv, envp);
        Sys::stub("EXECVEAT").map(|_| ())
    }

    fn exit(status: c_int) -> ! {
        syscalls::exit(status as u64).unwrap();
        panic!("Exit returned");
    }
    unsafe fn exit_thread(_stack_base: *mut (), _stack_size: usize) -> ! {
        // TODO
        Self::exit(0)
    }

    fn fchdir(fildes: c_int) -> Result<()> {
        let _ = fildes;
        Sys::stub("FCHDIR").map(|_| ())
    }

    fn fchmod(fildes: c_int, mode: mode_t) -> Result<()> {
        let _ = (fildes, mode);
        Ok(())
    }

    fn fchmodat(dirfd: c_int, path: Option<CStr>, mode: mode_t, flags: c_int) -> Result<()> {
        let _ = (dirfd, path, mode, flags);
        Ok(())
    }

    fn fchown(fildes: c_int, owner: uid_t, group: gid_t) -> Result<()> {
        let _ = (fildes, owner, group);
        Sys::stub("FCHOWN").map(|_| ())
    }

    fn fdatasync(fildes: c_int) -> Result<()> {
        let _ = fildes;
        Sys::stub("FDATASYNC").map(|_| ())
    }

    fn flock(fd: c_int, operation: c_int) -> Result<()> {
        let _ = (fd, operation);
        Sys::stub("FLOCK").map(|_| ())
    }

    fn fstat(fildes: c_int, mut buf: Out<stat>) -> Result<()> {
        let empty = b"\0";
        let empty_ptr = empty.as_ptr() as *const c_char;
        e_raw(unsafe {
            process_result(file_info(
                false,
                true,
                empty_ptr,
                buf.as_mut_ptr() as *mut u8,
                fildes as u64,
            ))
        })
        .map(|_| ())
    }

    fn fstatat(fildes: c_int, path: Option<CStr>, mut buf: Out<stat>, flags: c_int) -> Result<()> {
        let _ = (fildes, path, buf.as_mut_ptr(), flags);
        Sys::stub("NEWFSTATAT").map(|_| ())
    }

    fn fstatvfs(fildes: c_int, mut buf: Out<statvfs>) -> Result<()> {
        let buf = buf.as_mut_ptr();

        let mut kbuf = linux_statfs::default();
        let kbuf_ptr = &mut kbuf as *mut linux_statfs;
        let _ = (fildes, kbuf_ptr);
        Sys::stub("FSTATFS")?;

        if !buf.is_null() {
            unsafe {
                (*buf).f_bsize = kbuf.f_bsize as c_ulong;
                (*buf).f_frsize = if kbuf.f_frsize != 0 {
                    kbuf.f_frsize
                } else {
                    kbuf.f_bsize
                } as c_ulong;
                (*buf).f_blocks = kbuf.f_blocks;
                (*buf).f_bfree = kbuf.f_bfree;
                (*buf).f_bavail = kbuf.f_bavail;
                (*buf).f_files = kbuf.f_files;
                (*buf).f_ffree = kbuf.f_ffree;
                (*buf).f_favail = kbuf.f_ffree;
                (*buf).f_fsid = kbuf.f_fsid as c_ulong;
                (*buf).f_flag = kbuf.f_flags as c_ulong;
                (*buf).f_namemax = kbuf.f_namelen as c_ulong;
            }
        }
        Ok(())
    }

    fn fcntl(fildes: c_int, cmd: c_int, arg: c_ulonglong) -> Result<c_int> {
        let command = ControlCommand::from_linux(cmd).ok_or(Errno(EINVAL))?;
        e_raw(process_result(control_object(fildes as u64, command, arg))).map(|f| f as c_int)
    }

    unsafe fn fork() -> Result<pid_t> {
        e_raw(process_result(syscalls::fork())).map(|i| i as pid_t)
    }

    fn fpath(fildes: c_int, out: &mut [u8]) -> Result<usize> {
        let proc_path = format!("/proc/self/fd/{}\0", fildes).into_bytes();
        Self::readlink(CStr::from_bytes_with_nul(&proc_path).unwrap(), out)
    }

    fn fsync(fildes: c_int) -> Result<()> {
        let _ = fildes;
        Sys::stub("FSYNC").map(|_| ())
    }

    fn ftruncate(fildes: c_int, length: off_t) -> Result<()> {
        let _ = (fildes, length);
        Sys::stub("FTRUNCATE").map(|_| ())
    }

    #[inline]
    unsafe fn futex_wait(addr: *mut u32, val: u32, deadline: Option<&timespec>) -> Result<()> {
        e_raw(process_result(futex::wait(addr, u64::from(val)))).map(|_| ())
    }
    #[inline]
    unsafe fn futex_wake(addr: *mut u32, num: u32) -> Result<u32> {
        e_raw(process_result(futex::wake(addr, u64::from(num)))).map(|i| i as u32)
    }

    unsafe fn futimens(fd: c_int, times: *const timespec) -> Result<()> {
        let _ = (fd, times);
        Sys::stub("UTIMENSAT").map(|_| ())
    }

    unsafe fn utimens(path: CStr, times: *const timespec) -> Result<()> {
        let _ = (path, times);
        Sys::stub("UTIMENSAT").map(|_| ())
    }

    fn getcwd(mut buf: Out<[u8]>) -> Result<()> {
        unsafe {
            get_current_directory(slice::from_raw_parts_mut(
                buf.as_mut_ptr() as *mut u8,
                buf.len(),
            ))
        };
        Ok(())
    }

    fn getdents(fd: c_int, buf: &mut [u8], _off: u64) -> Result<usize> {
        e_raw(process_result(directory_contents(
            fd as u64,
            buf.as_mut_ptr(),
            buf.len() as u64,
        )))
    }
    fn dir_seek(fd: c_int, off: u64) -> Result<()> {
        let _ = (fd, off);
        Sys::stub("LSEEK").map(|_| ())
    }
    unsafe fn dent_reclen_offset(this_dent: &[u8], offset: usize) -> Option<(u16, u64)> {
        let dent = this_dent.as_ptr().cast::<dirent>();
        Some((unsafe { (*dent).d_reclen }, unsafe { (*dent).d_off } as u64))
    }

    fn getegid() -> gid_t {
        0
    }

    fn geteuid() -> uid_t {
        0
    }

    fn getgid() -> gid_t {
        0
    }

    fn getgroups(mut list: Out<[gid_t]>) -> Result<c_int> {
        Ok(0)
    }

    fn getpagesize() -> usize {
        4096
    }

    fn getpgid(pid: pid_t) -> Result<pid_t> {
        // TODO
        Ok(getpid())
    }

    fn getpid() -> pid_t {
        get_process_id().unwrap() as i32
    }

    fn getppid() -> pid_t {
        get_process_parent_id().unwrap() as i32
    }

    fn getpriority(which: c_int, who: id_t) -> Result<c_int> {
        let _ = (which, who);
        Ok(Sys::stub("GETPRIORITY")? as c_int)
    }

    fn getrandom(buf: &mut [u8], flags: c_uint) -> Result<usize> {
        let _ = (buf, flags);
        Sys::stub("GETRANDOM")
    }

    fn getrlimit(resource: c_int, mut rlim: Out<rlimit>) -> Result<()> {
        let _ = (resource, rlim.as_mut_ptr());
        Sys::stub("GETRLIMIT").map(|_| ())
    }

    fn getresgid(
        rgid: Option<Out<gid_t>>,
        egid: Option<Out<gid_t>>,
        sgid: Option<Out<gid_t>>,
    ) -> Result<()> {
        let _ = (rgid, egid, sgid);
        Sys::stub("GETRESGID").map(|_| ())
    }
    fn getresuid(
        ruid: Option<Out<uid_t>>,
        euid: Option<Out<uid_t>>,
        suid: Option<Out<uid_t>>,
    ) -> Result<()> {
        let _ = (ruid, euid, suid);
        Sys::stub("GETRESUID").map(|_| ())
    }

    unsafe fn setrlimit(resource: c_int, rlimit: *const rlimit) -> Result<()> {
        let _ = (resource, rlimit);
        Sys::stub("SETRLIMIT").map(|_| ())
    }

    fn getrusage(who: c_int, mut r_usage: Out<rusage>) -> Result<()> {
        let _ = (who, r_usage.as_mut_ptr());
        Sys::stub("GETRUSAGE").map(|_| ())
    }

    fn getsid(pid: pid_t) -> Result<pid_t> {
        let _ = pid;
        Ok(Sys::stub("GETSID")? as pid_t)
    }

    fn gettid() -> pid_t {
        // Always successful
        get_thread_id().unwrap() as i32
    }

    fn gettimeofday(mut tp: Out<timeval>, tzp: Option<Out<timezone>>) -> Result<()> {
        let nanoseconds = e_raw(process_result(get_current_time()))? as u64;

        unsafe {
            let tv = tp.as_mut_ptr();
            (*tv).tv_sec = (nanoseconds / 1_000_000_000) as time_t;
            (*tv).tv_usec = ((nanoseconds % 1_000_000_000) / 1_000) as suseconds_t;
        }

        if let Some(mut tzp) = tzp {
            tzp.write(timezone {
                tz_minuteswest: 0,
                tz_dsttime: 0,
            });
        }

        Ok(())
    }

    fn getuid() -> uid_t {
        0
    }

    #[cfg(any(target_arch = "x86_64", target_arch = "x86"))]
    fn lchown(path: CStr, owner: uid_t, group: gid_t) -> Result<()> {
        let _ = (path, owner, group);
        Sys::stub("LCHOWN").map(|_| ())
    }

    #[cfg(target_arch = "aarch64")]
    fn lchown(path: CStr, owner: uid_t, group: gid_t) -> Result<()> {
        let _ = (path, owner, group);
        Sys::stub("FCHOWNAT").map(|_| ())
    }

    fn link(path1: CStr, path2: CStr) -> Result<()> {
        e_raw(process_result(link_file(path1.as_ptr(), path2.as_ptr()))).map(|_| ())
    }

    fn lseek(fildes: c_int, offset: off_t, whence: c_int) -> Result<off_t> {
        let _ = (fildes, offset, whence);
        Ok(Sys::stub("LSEEK")? as off_t)
    }

    fn mkdirat(dir_fildes: c_int, path: CStr, mode: mode_t) -> Result<()> {
        let _ = mode;
        if dir_fildes != AT_FDCWD {
            return Err(Errno(ENOSYS));
        }

        e_raw(process_result(create_directory(path.as_ptr(), false))).map(|_| ())
    }

    fn mkdir(path: CStr, mode: mode_t) -> Result<()> {
        Sys::mkdirat(AT_FDCWD, path, mode)
    }

    fn mknodat(dir_fildes: c_int, path: CStr, mode: mode_t, dev: dev_t) -> Result<()> {
        // Note: dev_t is c_long (i64) and __kernel_dev_t is u32; So we need to cast it
        //       and check for overflow
        let k_dev: c_uint = dev as c_uint;
        if dev_t::from(k_dev) != dev {
            return Err(Errno(EINVAL));
        }

        let _ = (dir_fildes, path, mode, k_dev);
        Sys::stub("MKNODAT").map(|_| ())
    }

    fn mknod(path: CStr, mode: mode_t, dev: dev_t) -> Result<()> {
        Sys::mknodat(AT_FDCWD, path, mode, dev)
    }

    fn mkfifoat(dir_fd: c_int, path: CStr, mode: mode_t) -> Result<()> {
        Sys::mknodat(dir_fd, path, mode | S_IFIFO, 0)
    }

    fn mkfifo(path: CStr, mode: mode_t) -> Result<()> {
        Sys::mknod(path, mode | S_IFIFO, 0)
    }

    unsafe fn mlock(addr: *const c_void, len: usize) -> Result<()> {
        let _ = (addr, len);
        Sys::stub("MLOCK").map(|_| ())
    }

    unsafe fn mlockall(flags: c_int) -> Result<()> {
        let _ = flags;
        Sys::stub("MLOCKALL").map(|_| ())
    }

    unsafe fn mmap(
        addr: *mut c_void,
        len: usize,
        prot: c_int,
        flags: c_int,
        fildes: c_int,
        off: off_t,
    ) -> Result<*mut c_void> {
        if len == 0 {
            return Err(Errno(EINVAL));
        }

        if (flags & (MAP_FIXED | MAP_FIXED_NOREPLACE)) != 0 {
            return Err(Errno(ENOSYS));
        }

        if !addr.is_null() {
            return Err(Errno(ENOSYS));
        }

        let unsupported_prot = prot & !(PROT_NONE | PROT_READ | PROT_WRITE | PROT_EXEC);
        if unsupported_prot != 0 {
            return Err(Errno(EINVAL));
        }

        // The kernel AllocateMem path currently only provides fresh anonymous pages.
        // Translate the mmap protection bits into Seele page permissions.
        let supported_prot = PROT_NONE | PROT_READ | PROT_WRITE | PROT_EXEC;
        if (prot & supported_prot) != prot {
            return Err(Errno(ENOSYS));
        }

        let _is_stack = (flags & MAP_STACK) != 0;
        let permissions = prot_to_permissions(prot);

        // Maps the object if its not a anonymous map.
        // an anonymous map basically means you just want
        // a chunk of memory, and you dont want to map a object
        if (flags & MAP_ANON) == 0 {
            if fildes < 0 || off < 0 {
                return Err(Errno(EINVAL));
            }
            if (off as usize) % 4096 != 0 {
                return Err(Errno(EINVAL));
            }

            return e_raw(process_result(mmap_object(
                fildes as u64,
                len.div_ceil(4096) as u64,
                off as u64,
                permissions,
            )))
            .map(|r| r as *mut c_void);
        }

        // Just allocates memory if its a anonymous map
        match allocate_mem(len as u64, flags as u64, permissions) {
            Ok(addr) => Ok(addr as *mut c_void),
            Err(_) => Err(Errno(EIO)),
        }
    }

    unsafe fn mremap(
        addr: *mut c_void,
        len: usize,
        new_len: usize,
        flags: c_int,
        args: *mut c_void,
    ) -> Result<*mut c_void> {
        let _ = (addr, len, new_len, flags, args);
        Ok(Sys::stub("MREMAP")? as *mut c_void)
    }

    unsafe fn mprotect(addr: *mut c_void, len: usize, prot: c_int) -> Result<()> {
        e_raw(process_result(update_mem_perms(
            addr as u64,
            len as u64,
            prot_to_permissions(prot),
        )))
        .map(|_| ())
    }

    unsafe fn msync(addr: *mut c_void, len: usize, flags: c_int) -> Result<()> {
        let _ = (addr, len, flags);
        Sys::stub("MSYNC").map(|_| ())
    }

    unsafe fn munlock(addr: *const c_void, len: usize) -> Result<()> {
        let _ = (addr, len);
        Sys::stub("MUNLOCK").map(|_| ())
    }

    unsafe fn munlockall() -> Result<()> {
        Sys::stub("MUNLOCKALL").map(|_| ())
    }

    unsafe fn munmap(addr: *mut c_void, len: usize) -> Result<()> {
        e_raw(process_result(deallocate_mem(addr as u64, len as u64))).map(|_| ())
    }

    unsafe fn madvise(addr: *mut c_void, len: usize, flags: c_int) -> Result<()> {
        let _ = (addr, len, flags);
        Sys::stub("MADVISE").map(|_| ())
    }

    unsafe fn nanosleep(rqtp: *const timespec, rmtp: *mut timespec) -> Result<()> {
        if rqtp.is_null() {
            return Err(Errno(EINVAL));
        }

        let requested = unsafe { &*rqtp };
        if requested.tv_sec < 0 || requested.tv_nsec < 0 || requested.tv_nsec >= 1_000_000_000 {
            return Err(Errno(EINVAL));
        }

        let seconds = u64::try_from(requested.tv_sec).map_err(|_| Errno(EINVAL))?;
        let nanoseconds = u64::try_from(requested.tv_nsec).map_err(|_| Errno(EINVAL))?;
        let total = seconds
            .checked_mul(1_000_000_000)
            .and_then(|value| value.checked_add(nanoseconds))
            .ok_or(Errno(EINVAL))?;

        e_raw(process_result(sleep(total)))?;

        if !rmtp.is_null() {
            unsafe {
                (*rmtp).tv_sec = 0;
                (*rmtp).tv_nsec = 0;
            }
        }

        Ok(())
    }

    fn open(path: CStr, oflag: c_int, mode: mode_t) -> Result<c_int> {
        if (oflag & O_CREAT) != 0 && (oflag & O_EXCL) != 0 && Self::access(path, F_OK).is_ok() {
            return Err(Errno(EEXIST));
        }

        if let Some(device) = device_from_path(path.to_str().map_err(|_| Errno(EINVAL))?) {
            return e_raw(process_result(open_device(device))).map(|fd| fd as c_int);
        }

        e_raw(process_result(open_file(
            path.as_ptr(),
            (oflag & O_CREAT) != 0,
        )))
        .map(|fd| fd as c_int)
    }

    fn pipe2(mut fildes: Out<[c_int; 2]>, flags: c_int) -> Result<()> {
        let _ = (fildes.as_mut_ptr(), flags);
        Sys::stub("PIPE2").map(|_| ())
    }

    fn posix_fallocate(fd: c_int, offset: u64, length: NonZeroU64) -> Result<()> {
        let _ = (fd, offset, length);
        Sys::stub("FALLOCATE").map(|_| ())
    }

    fn posix_getdents(fildes: c_int, buf: &mut [u8]) -> Result<usize> {
        let current_offset = Self::lseek(fildes, 0, SEEK_CUR)? as u64;
        let bytes_read = Self::getdents(fildes, buf, current_offset)?;
        if bytes_read == 0 {
            return Ok(0);
        }
        let mut bytes_processed = 0;
        let mut next_offset = current_offset;

        while bytes_processed < bytes_read {
            let remaining_slice = &buf[bytes_processed..];
            let (reclen, opaque_next) =
                unsafe { Self::dent_reclen_offset(remaining_slice, bytes_processed) }
                    .ok_or(Errno(EIO))?;
            if reclen == 0 {
                return Err(Errno(EIO));
            }

            bytes_processed += reclen as usize;
            next_offset = opaque_next;
        }

        Self::lseek(fildes, next_offset as off_t, SEEK_SET)?;
        Ok(bytes_read)
    }

    #[cfg(target_arch = "x86_64")]
    unsafe fn rlct_clone(
        stack: *mut usize,
        _os_specific: &mut OsSpecific,
    ) -> Result<crate::pthread::OsTid> {
        let _ = (stack, _os_specific);
        let tid = Sys::stub("CLONE")?;
        Ok(crate::pthread::OsTid { thread_id: tid })
    }

    #[cfg(target_arch = "aarch64")]
    unsafe fn rlct_clone(
        stack: *mut usize,
        _os_specific: &mut OsSpecific,
    ) -> Result<crate::pthread::OsTid> {
        todo!("rlct_clone not implemented for aarch64 yet")
    }

    unsafe fn rlct_kill(os_tid: crate::pthread::OsTid, signal: usize) -> Result<()> {
        let _ = (os_tid, signal);
        Sys::stub("TGKILL").map(|_| ())
    }

    fn current_os_tid() -> crate::pthread::OsTid {
        crate::pthread::OsTid {
            thread_id: Sys::gettid() as usize,
        }
    }

    fn read(fildes: c_int, buf: &mut [u8]) -> Result<usize> {
        e_raw(process_result(read_object(fildes as u64, buf)))
    }
    fn pread(fildes: c_int, buf: &mut [u8], off: off_t) -> Result<usize> {
        let _ = (fildes, buf, off);
        Sys::stub("PREAD64")
    }

    fn readlink(pathname: CStr, out: &mut [u8]) -> Result<usize> {
        let _ = (pathname, out);
        Sys::stub("READLINKAT")
    }

    fn readlinkat(dirfd: c_int, pathname: CStr, out: &mut [u8]) -> Result<usize> {
        let _ = (dirfd, pathname, out);
        Sys::stub("READLINKAT")
    }

    fn rename(old: CStr, new: CStr) -> Result<()> {
        let _ = (old, new);
        Sys::stub("RENAMEAT").map(|_| ())
    }

    fn renameat(old_dir: c_int, old_path: CStr, new_dir: c_int, new_path: CStr) -> Result<()> {
        let _ = (old_dir, old_path, new_dir, new_path);
        Sys::stub("RENAMEAT").map(|_| ())
    }

    fn renameat2(
        old_dir: c_int,
        old_path: CStr,
        new_dir: c_int,
        new_path: CStr,
        flags: c_uint,
    ) -> Result<()> {
        let _ = (old_dir, old_path, new_dir, new_path, flags);
        Sys::stub("RENAMEAT2").map(|_| ())
    }

    fn rmdir(path: CStr) -> Result<()> {
        let _ = path;
        Sys::stub("UNLINKAT").map(|_| ())
    }

    fn sched_yield() -> Result<()> {
        Sys::stub("SCHED_YIELD").map(|_| ())
    }

    unsafe fn setgroups(size: size_t, list: *const gid_t) -> Result<()> {
        Ok(())
    }

    fn setpgid(pid: pid_t, pgid: pid_t) -> Result<()> {
        let _ = (pid, pgid);
        Sys::stub("SETPGID").map(|_| ())
    }

    fn setpriority(which: c_int, who: id_t, prio: c_int) -> Result<()> {
        let _ = (which, who, prio);
        Sys::stub("SETPRIORITY").map(|_| ())
    }

    fn setresgid(rgid: gid_t, egid: gid_t, sgid: gid_t) -> Result<()> {
        let _ = (rgid, egid, sgid);
        Sys::stub("SETRESGID").map(|_| ())
    }

    fn setresuid(ruid: uid_t, euid: uid_t, suid: uid_t) -> Result<()> {
        let _ = (ruid, euid, suid);
        Sys::stub("SETRESUID").map(|_| ())
    }

    fn setsid() -> Result<c_int> {
        Ok(Sys::stub("SETSID")? as c_int)
    }

    fn symlink(path1: CStr, path2: CStr) -> Result<()> {
        let _ = (path1, path2);
        Sys::stub("SYMLINKAT").map(|_| ())
    }

    fn sync() -> Result<()> {
        Sys::stub("SYNC").map(|_| ())
    }

    fn timer_create(clock_id: clockid_t, evp: &sigevent, mut timerid: Out<timer_t>) -> Result<()> {
        let _ = (clock_id, evp);
        if !timerid.as_mut_ptr().is_null() {
            unsafe {
                *timerid.as_mut_ptr() = core::ptr::null_mut();
            }
        }
        Sys::stub("TIMER_CREATE").map(|_| ())
    }

    fn timer_delete(timerid: timer_t) -> Result<()> {
        let _ = timerid;
        Sys::stub("TIMER_DELETE").map(|_| ())
    }

    fn timer_gettime(timerid: timer_t, mut value: Out<itimerspec>) -> Result<()> {
        let _ = (timerid, value.as_mut_ptr());
        Sys::stub("TIMER_GETTIME").map(|_| ())
    }

    fn timer_settime(
        timerid: timer_t,
        flags: c_int,
        value: &itimerspec,
        ovalue: Option<Out<itimerspec>>,
    ) -> Result<()> {
        let _ = (timerid, flags, value, ovalue);
        Sys::stub("TIMER_SETTIME").map(|_| ())
    }

    fn umask(mask: mode_t) -> mode_t {
        static UMASK: Mutex<mode_t> = Mutex::new(0o022);

        let mut umask_locked = UMASK.lock();
        let old = *umask_locked;
        *umask_locked = mask & 0o777;
        old
    }

    fn uname(mut utsname: Out<utsname>) -> Result<()> {
        let mut system_info = SystemInfo::new("", "");

        get_system_info(&mut system_info as *mut SystemInfo);

        utsname.write(utsname::from(system_info));

        Ok(())
    }

    fn unlink(path: CStr) -> Result<()> {
        e_raw(process_result(delete_file(path.as_ptr()))).map(|_| ())
    }

    fn waitpid(pid: pid_t, stat_loc: Option<Out<c_int>>, options: c_int) -> Result<pid_t> {
        let status_ptr = stat_loc.map_or(core::ptr::null_mut(), |mut o| o.as_mut_ptr());
        loop {
            match e_raw(process_result(wait_for_process_exit(pid, status_ptr))) {
                Err(Errno(EAGAIN)) => continue,
                other => return other.map(|p| p as pid_t),
            }
        }
    }

    fn write(fildes: c_int, buf: &[u8]) -> Result<usize> {
        e_raw(process_result(write_object(fildes as u64, buf)))
    }

    fn pwrite(fildes: c_int, buf: &[u8], off: off_t) -> Result<usize> {
        let _ = (fildes, buf, off);
        Sys::stub("PWRITE64")
    }

    fn verify() -> bool {
        // GETPID on Linux is 39, which does not exist on Redox
        //e_raw(unsafe { sc::syscall5(sc::nr::GETPID, !0, !0, !0, !0, !0) }).is_ok()
        true
    }
}
