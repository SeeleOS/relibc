//! `pty.h` implementation.
//!
//! Non-POSIX, see <https://www.man7.org/linux/man-pages/man3/openpty.3.html>.

use core::{mem, ptr, slice};

use seele_sys::{syscalls::misc::create_pty, utils::process_result};

use crate::{
    header::{
        errno::ENOSYS, fcntl, limits, pthread, signal, sys_ioctl, sys_wait, termios, unistd, utmp,
    },
    platform::{
        self, ERRNO,
        sys::e_raw,
        types::{c_char, c_int, c_void},
    },
};

#[cfg(any(target_os = "linux", target_os = "seele"))]
#[path = "linux.rs"]
mod imp;

#[cfg(target_os = "redox")]
#[path = "redox.rs"]
mod imp;

/// See <https://www.man7.org/linux/man-pages/man3/openpty.3.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn openpty(
    amaster: *mut c_int,
    aslave: *mut c_int,
    namep: *mut c_char,
    termp: *const termios::termios,
    winp: *const sys_ioctl::winsize,
) -> c_int {
    if winp != core::ptr::null() || termp != core::ptr::null() || namep != core::ptr::null_mut() {
        ERRNO.set(ENOSYS);
        return -1;
    }

    if let Err(crate::error::Errno(errno)) = e_raw(process_result(create_pty(amaster, aslave))) {
        ERRNO.set(errno);
        return -1;
    }

    0
}

/// See <https://www.man7.org/linux/man-pages/man3/openpty.3.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn forkpty(
    pm: *mut c_int,
    name: *mut c_char,
    tio: *const termios::termios,
    ws: *const sys_ioctl::winsize,
) -> c_int {
    let mut m = 0;
    let mut s = 0;
    let mut ec = 0;
    let mut p: [c_int; 2] = [0; 2];
    let mut cs = 0;
    let mut pid = -1;
    let mut set = signal::sigset_t::default();
    let mut oldset = signal::sigset_t::default();

    if unsafe { openpty(&raw mut m, &raw mut s, name, tio, ws) } < 0 {
        return -1;
    }

    unsafe { signal::sigfillset(&raw mut set) };
    unsafe { signal::pthread_sigmask(signal::SIG_BLOCK, &raw const set, &raw mut oldset) };
    unsafe { pthread::pthread_setcancelstate(pthread::PTHREAD_CANCEL_DISABLE, &raw mut cs) };

    if unsafe { unistd::pipe2(p.as_mut_ptr(), fcntl::O_CLOEXEC) } != 0 {
        unistd::close(s);
    } else {
        pid = unsafe { unistd::fork() };
        if pid == 0 {
            unistd::close(m);
            unistd::close(p[0]);
            if unsafe { utmp::login_tty(s) } != 0 {
                unsafe {
                    unistd::write(
                        p[1],
                        platform::ERRNO.as_ptr().cast(),
                        mem::size_of_val(&platform::ERRNO),
                    )
                };
                unistd::_exit(127);
            }
            unistd::close(p[1]);
            unsafe { pthread::pthread_setcancelstate(cs, ptr::null_mut()) };
            unsafe {
                signal::pthread_sigmask(signal::SIG_SETMASK, &raw const oldset, ptr::null_mut())
            };
            return 0;
        }

        unistd::close(s);
        unistd::close(p[1]);

        if unsafe {
            unistd::read(
                p[0],
                ptr::from_mut::<c_int>(&mut ec).cast::<c_void>(),
                mem::size_of::<c_int>(),
            )
        } > 0
        {
            let mut status = 0;
            unsafe { sys_wait::waitpid(pid, &raw mut status, 0) };
            pid = -1;
            platform::ERRNO.set(ec);
        }
        unistd::close(p[0]);
    }
    if pid > 0 {
        unsafe { *pm = m };
    } else {
        unistd::close(m);
    }
    unsafe { pthread::pthread_setcancelstate(cs, ptr::null_mut()) };
    unsafe { signal::pthread_sigmask(signal::SIG_SETMASK, &raw const oldset, ptr::null_mut()) };
    pid
}
