//! `termios.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html>.

use seele_sys::abi::object::TerminalInfo as SeeleTerminalInfo;

use crate::{
    header::{
        errno,
        sys_ioctl::{self, winsize},
    },
    platform::{
        self,
        types::{c_int, c_ulong, c_void, pid_t},
    },
};

pub use self::sys::*;

#[cfg(any(target_os = "linux", target_os = "seele"))]
#[path = "linux.rs"]
pub mod sys;

#[cfg(target_os = "redox")]
#[path = "redox.rs"]
pub mod sys;

pub type cc_t = u8;
pub type speed_t = u32;
pub type tcflag_t = u32;

pub const TCOOFF: c_int = 0;
pub const TCOON: c_int = 1;
pub const TCIOFF: c_int = 2;
pub const TCION: c_int = 3;

pub const TCIFLUSH: c_int = 0;
pub const TCOFLUSH: c_int = 1;
pub const TCIOFLUSH: c_int = 2;

pub const TCSANOW: c_int = 0;
pub const TCSADRAIN: c_int = 1;
pub const TCSAFLUSH: c_int = 2;

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html>.
#[cfg(any(target_os = "linux", target_os = "seele"))]
#[repr(C)]
#[derive(Default, Clone)]
pub struct termios {
    pub c_iflag: tcflag_t,
    pub c_oflag: tcflag_t,
    pub c_cflag: tcflag_t,
    pub c_lflag: tcflag_t,
    pub c_line: cc_t,
    pub c_cc: [cc_t; NCCS],
    pub __c_ispeed: speed_t,
    pub __c_ospeed: speed_t,
}

impl self::termios {
    fn sane_defaults() -> Self {
        let mut termios = Self {
            c_iflag: (ICRNL | IXON) as u32,
            c_oflag: (OPOST | ONLCR) as u32,
            c_cflag: (B38400 | CS8 | CREAD | HUPCL) as u32,
            c_lflag: (ISIG | ICANON | ECHO | ECHOE | ECHOK | IEXTEN) as u32,
            c_line: 0,
            c_cc: [_POSIX_VDISABLE; NCCS],
            __c_ispeed: B38400 as u32,
            __c_ospeed: B38400 as u32,
        };

        termios.c_cc[VINTR] = 3;
        termios.c_cc[VQUIT] = 28;
        termios.c_cc[VERASE] = 127;
        termios.c_cc[VKILL] = 21;
        termios.c_cc[VEOF] = 4;
        termios.c_cc[VMIN] = 1;
        termios.c_cc[VTIME] = 0;
        termios.c_cc[VSTART] = 17;
        termios.c_cc[VSTOP] = 19;
        termios.c_cc[VSUSP] = 26;
        termios.c_cc[VREPRINT] = 18;
        termios.c_cc[VDISCARD] = 15;
        termios.c_cc[VWERASE] = 23;
        termios.c_cc[VLNEXT] = 22;

        termios
    }

    fn set_raw_mode(&mut self) {
        self.c_iflag &= !(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON) as u32;
        self.c_oflag &= !(OPOST as u32);
        self.c_lflag &= !(ECHO | ECHONL | ICANON | ISIG | IEXTEN) as u32;
        self.c_cflag &= !((CSIZE | PARENB) as u32);
        self.c_cflag |= CS8 as u32;
        self.c_cc[VMIN] = 1;
        self.c_cc[VTIME] = 0;
    }

    fn set_noncanonical_mode(&mut self) {
        // Seele currently only tracks whether line discipline is canonical.
        // Do not expand that into full cfmakeraw()-style semantics on tcgetattr,
        // or readline/bash will observe a tty state they never actually asked for.
        self.c_lflag &= !(ICANON as u32);
        self.c_cc[VMIN] = 1;
        self.c_cc[VTIME] = 0;
    }

    /// convert [`self`] to a [`SeeleTerminalInfo`], with an existing [`SeeleTerminalInfo`]
    pub fn as_seele_terminal_info(&self, current: SeeleTerminalInfo) -> SeeleTerminalInfo {
        let echo = self.c_lflag & ECHO as u32 != 0;
        let canonical = self.c_lflag & ICANON as u32 != 0;
        let echo_newline = echo || self.c_lflag & ECHONL as u32 != 0;
        let echo_delete = self.c_lflag & (ECHO | ECHOE) as u32 == (ECHO | ECHOE) as u32;

        SeeleTerminalInfo {
            rows: current.rows,
            cols: current.cols,
            echo,
            canonical,
            echo_newline,
            echo_delete,
        }
    }
}

impl From<SeeleTerminalInfo> for termios {
    fn from(terminal_info: SeeleTerminalInfo) -> Self {
        let mut termios = termios::sane_defaults();

        if !terminal_info.canonical {
            termios.set_noncanonical_mode();
        }

        if terminal_info.echo {
            termios.c_lflag |= ECHO as u32;
        } else {
            termios.c_lflag &= !(ECHO as u32);
        }

        if terminal_info.echo_newline {
            termios.c_lflag |= ECHONL as u32;
        } else {
            termios.c_lflag &= !(ECHONL as u32);
        }

        if terminal_info.echo_delete {
            termios.c_lflag |= ECHOE as u32;
        } else {
            termios.c_lflag &= !(ECHOE as u32);
        }

        termios
    }
}

// Must match structure in redox_termios
/// See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html>.
#[cfg(target_os = "redox")]
#[repr(C)]
#[derive(Default, Clone)]
pub struct termios {
    pub c_iflag: tcflag_t,
    pub c_oflag: tcflag_t,
    pub c_cflag: tcflag_t,
    pub c_lflag: tcflag_t,
    pub c_cc: [cc_t; NCCS],
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetattr.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcgetattr(fd: c_int, out: *mut termios) -> c_int {
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCGETS, out as *mut c_void) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsetattr.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcsetattr(fd: c_int, act: c_int, value: *const termios) -> c_int {
    if act < 0 || act > 2 {
        platform::ERRNO.set(errno::EINVAL);
        return -1;
    }
    // This is safe because ioctl shouldn't modify the value
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCSETS + act as c_ulong, value as *mut c_void) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetsid.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcgetsid(fd: c_int) -> pid_t {
    let mut sid = 0;
    if unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TIOCGSID, (&raw mut sid) as *mut c_void) } < 0 {
        return -1;
    }
    sid
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetispeed.html>.
#[cfg(any(target_os = "linux", target_os = "seele"))]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfgetispeed(termios_p: *const termios) -> speed_t {
    unsafe { (*termios_p).__c_ispeed }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetispeed.html>.
#[cfg(target_os = "redox")]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfgetispeed(termios_p: *const termios) -> speed_t {
    //TODO
    0
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetospeed.html>.
#[cfg(any(target_os = "linux", target_os = "seele"))]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfgetospeed(termios_p: *const termios) -> speed_t {
    unsafe { (*termios_p).__c_ospeed }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetospeed.html>.
#[cfg(target_os = "redox")]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfgetospeed(termios_p: *const termios) -> speed_t {
    //TODO
    0
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetispeed.html>.
#[cfg(any(target_os = "linux", target_os = "seele"))]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfsetispeed(termios_p: *mut termios, speed: speed_t) -> c_int {
    match speed as usize {
        B0..=B38400 | B57600..=B4000000 => {
            unsafe { (*termios_p).__c_ispeed = speed };
            0
        }
        _ => {
            platform::ERRNO.set(errno::EINVAL);
            -1
        }
    }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetispeed.html>.
#[cfg(target_os = "redox")]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfsetispeed(termios_p: *mut termios, speed: speed_t) -> c_int {
    //TODO
    platform::ERRNO.set(errno::EINVAL);
    -1
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetospeed.html>.
#[cfg(any(target_os = "linux", target_os = "seele"))]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfsetospeed(termios_p: *mut termios, speed: speed_t) -> c_int {
    match speed as usize {
        B0..=B38400 | B57600..=B4000000 => {
            unsafe { (*termios_p).__c_ospeed = speed };
            0
        }
        _ => {
            platform::ERRNO.set(errno::EINVAL);
            -1
        }
    }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetospeed.html>.
#[cfg(target_os = "redox")]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfsetospeed(termios_p: *mut termios, speed: speed_t) -> c_int {
    //TODO
    platform::ERRNO.set(errno::EINVAL);
    -1
}

/// Non-POSIX, 4.4 BSD extension
///
/// See <https://www.man7.org/linux/man-pages/man3/cfsetispeed.3.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfsetspeed(termios_p: *mut termios, speed: speed_t) -> c_int {
    let r = unsafe { cfsetispeed(termios_p, speed) };
    if r < 0 {
        return r;
    }
    unsafe { cfsetospeed(termios_p, speed) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcflush.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcflush(fd: c_int, queue: c_int) -> c_int {
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCFLSH, queue as *mut c_void) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcdrain.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcdrain(fd: c_int) -> c_int {
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCSBRK, 1 as *mut _) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsendbreak.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcsendbreak(fd: c_int, _dur: c_int) -> c_int {
    // non-zero duration is ignored by musl due to it being
    // implementation-defined. we do the same.
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCSBRK, 0 as *mut _) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetwinsize.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcgetwinsize(fd: c_int, sws: *mut winsize) -> c_int {
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TIOCGWINSZ, sws.cast()) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsetwinsize.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcsetwinsize(fd: c_int, sws: *const winsize) -> c_int {
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TIOCSWINSZ, (sws as *mut winsize).cast()) }
}

/// See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcflow.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tcflow(fd: c_int, action: c_int) -> c_int {
    // non-zero duration is ignored by musl due to it being
    // implementation-defined. we do the same.
    unsafe { sys_ioctl::ioctl(fd, sys_ioctl::TCXONC, action as *mut _) }
}

/// Non-POSIX, BSD extension
///
/// See <https://www.man7.org/linux/man-pages/man3/cfmakeraw.3.html>.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn cfmakeraw(termios_p: *mut termios) {
    unsafe {
        (*termios_p).c_iflag &=
            !(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON) as u32;
        (*termios_p).c_oflag &= !OPOST as u32;
        (*termios_p).c_lflag &= !(ECHO | ECHONL | ICANON | ISIG | IEXTEN) as u32;
        (*termios_p).c_cflag &= !(CSIZE | PARENB) as u32;
        (*termios_p).c_cflag |= CS8 as u32;
        (*termios_p).c_cc[VMIN] = 1;
        (*termios_p).c_cc[VTIME] = 0;
    }
}
