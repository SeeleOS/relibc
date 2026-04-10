//! `spawn.h` implementation.
//!
//! See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/posix_spawn.html>.

use alloc::{boxed::Box, ffi::CString, vec::Vec};
use core::{mem, ptr};

use crate::{
    c_str::CStr,
    error::Errno,
    header::{
        errno::{EBADF, EINVAL, ENOENT, ENOMEM, ENOSYS},
        sched::sched_param,
        signal::{sigprocmask, sigset_t, SIG_SETMASK},
        unistd::{_exit, chdir, execve, execvp, fchdir, fork, setpgid},
    },
    platform::{
        self,
        types::{c_char, c_int, c_short, c_void, mode_t, pid_t},
        Pal, Sys,
    },
};

pub const POSIX_SPAWN_RESETIDS: c_short = 0x01;
pub const POSIX_SPAWN_SETPGROUP: c_short = 0x02;
pub const POSIX_SPAWN_SETSIGDEF: c_short = 0x04;
pub const POSIX_SPAWN_SETSIGMASK: c_short = 0x08;
pub const POSIX_SPAWN_SETSCHEDPARAM: c_short = 0x10;
pub const POSIX_SPAWN_SETSCHEDULER: c_short = 0x20;
pub const POSIX_SPAWN_USEVFORK: c_short = 0x40;

#[repr(C)]
#[derive(Clone, Copy)]
pub struct posix_spawnattr_t {
    pub __flags: c_short,
    pub __pgroup: pid_t,
    pub __sd: sigset_t,
    pub __ss: sigset_t,
    pub __sp: sched_param,
    pub __policy: c_int,
    pub __pad: [c_int; 8],
}

#[repr(C)]
pub struct posix_spawn_file_actions_t {
    pub __actions: *mut c_void,
    pub __pad: [usize; 15],
}

enum FileAction {
    Open {
        fd: c_int,
        path: CString,
        oflag: c_int,
        mode: mode_t,
    },
    Close(c_int),
    Dup2 { src: c_int, dst: c_int },
    Chdir(CString),
    Fchdir(c_int),
}

fn file_actions_mut<'a>(
    actions: *mut posix_spawn_file_actions_t,
) -> Result<&'a mut Vec<FileAction>, Errno> {
    let actions = unsafe { actions.as_mut() }.ok_or(Errno(EINVAL))?;
    if actions.__actions.is_null() {
        return Err(Errno(EINVAL));
    }

    Ok(unsafe { &mut *actions.__actions.cast::<Vec<FileAction>>() })
}

fn file_actions_ref<'a>(
    actions: *const posix_spawn_file_actions_t,
) -> Result<&'a Vec<FileAction>, Errno> {
    let actions = unsafe { actions.as_ref() }.ok_or(Errno(EINVAL))?;
    if actions.__actions.is_null() {
        return Err(Errno(EINVAL));
    }

    Ok(unsafe { &*actions.__actions.cast::<Vec<FileAction>>() })
}

fn clone_c_string(ptr: *const c_char) -> Result<CString, Errno> {
    let s = unsafe { ptr.as_ref() }.ok_or(Errno(EINVAL))?;
    let s = unsafe { CStr::from_ptr(s) };
    CString::new(s.to_bytes()).map_err(|_| Errno(EINVAL))
}

fn apply_attrs(attr: Option<&posix_spawnattr_t>) -> Result<(), Errno> {
    let Some(attr) = attr else {
        return Ok(());
    };

    if attr.__flags & POSIX_SPAWN_SETSIGMASK != 0 {
        if unsafe { sigprocmask(SIG_SETMASK, &raw const attr.__ss, ptr::null_mut()) } < 0 {
            return Err(Errno(platform::ERRNO.get()));
        }
    }

    if attr.__flags & POSIX_SPAWN_SETPGROUP != 0 {
        if setpgid(0, attr.__pgroup) < 0 {
            return Err(Errno(platform::ERRNO.get()));
        }
    }

    if attr.__flags & (POSIX_SPAWN_RESETIDS
        | POSIX_SPAWN_SETSIGDEF
        | POSIX_SPAWN_SETSCHEDPARAM
        | POSIX_SPAWN_SETSCHEDULER
        | POSIX_SPAWN_USEVFORK)
        != 0
    {
        return Err(Errno(ENOSYS));
    }

    Ok(())
}

fn apply_file_actions(actions: Option<&Vec<FileAction>>) -> Result<(), Errno> {
    let Some(actions) = actions else {
        return Ok(());
    };

    for action in actions {
        match action {
            FileAction::Open {
                fd,
                path,
                oflag,
                mode,
            } => {
                let opened = Sys::open(path.as_c_str().into(), *oflag, *mode)
                    .map_err(|err| err.sync())?;
                if opened != *fd {
                    Sys::dup2(opened, *fd).map_err(|err| err.sync())?;
                }
            }
            FileAction::Close(fd) => {
                Sys::close(*fd).map_err(|err| err.sync())?;
            }
            FileAction::Dup2 { src, dst } => {
                Sys::dup2(*src, *dst).map_err(|err| err.sync())?;
            }
            FileAction::Chdir(path) => {
                let rc = unsafe { chdir(path.as_ptr()) };
                if rc < 0 {
                    return Err(Errno(platform::ERRNO.get()));
                }
            }
            FileAction::Fchdir(fd) => {
                if fchdir(*fd) < 0 {
                    return Err(Errno(platform::ERRNO.get()));
                }
            }
        }
    }

    Ok(())
}

fn spawn_inner(
    pid: *mut pid_t,
    path: *const c_char,
    file_actions: *const posix_spawn_file_actions_t,
    attr: *const posix_spawnattr_t,
    argv: *const *mut c_char,
    envp: *const *mut c_char,
    search_path: bool,
) -> c_int {
    if pid.is_null() || path.is_null() || argv.is_null() {
        return EINVAL;
    }

    let actions = if file_actions.is_null() {
        None
    } else {
        match file_actions_ref(file_actions) {
            Ok(actions) => Some(actions),
            Err(Errno(err)) => return err,
        }
    };
    let attr = unsafe { attr.as_ref() };

    let child = unsafe { fork() };
    if child < 0 {
        return platform::ERRNO.get();
    }

    if child == 0 {
        if apply_attrs(attr).is_err() || apply_file_actions(actions).is_err() {
            _exit(127);
        }

        if search_path {
            unsafe { execvp(path, argv) };
        } else {
            unsafe { execve(path, argv, envp) };
        }
        _exit(if platform::ERRNO.get() == ENOENT { 127 } else { 126 });
    }

    unsafe { pid.write(child) };
    0
}

/// See POSIX `posix_spawn`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn(
    pid: *mut pid_t,
    path: *const c_char,
    file_actions: *const posix_spawn_file_actions_t,
    attr: *const posix_spawnattr_t,
    argv: *const *mut c_char,
    envp: *const *mut c_char,
) -> c_int {
    spawn_inner(pid, path, file_actions, attr, argv, envp, false)
}

/// See POSIX `posix_spawnp`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnp(
    pid: *mut pid_t,
    file: *const c_char,
    file_actions: *const posix_spawn_file_actions_t,
    attr: *const posix_spawnattr_t,
    argv: *const *mut c_char,
    envp: *const *mut c_char,
) -> c_int {
    spawn_inner(pid, file, file_actions, attr, argv, envp, true)
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_init(attr: *mut posix_spawnattr_t) -> c_int {
    let Some(attr) = (unsafe { attr.as_mut() }) else {
        return EINVAL;
    };
    *attr = posix_spawnattr_t {
        __flags: 0,
        __pgroup: 0,
        __sd: 0,
        __ss: 0,
        __sp: sched_param { sched_priority: 0 },
        __policy: 0,
        __pad: [0; 8],
    };
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_destroy(attr: *mut posix_spawnattr_t) -> c_int {
    if attr.is_null() {
        return EINVAL;
    }
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setflags(
    attr: *mut posix_spawnattr_t,
    flags: c_short,
) -> c_int {
    let Some(attr) = (unsafe { attr.as_mut() }) else {
        return EINVAL;
    };
    attr.__flags = flags;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getflags(
    attr: *const posix_spawnattr_t,
    flags: *mut c_short,
) -> c_int {
    let (Some(attr), Some(flags)) = (unsafe { attr.as_ref() }, unsafe { flags.as_mut() }) else {
        return EINVAL;
    };
    *flags = attr.__flags;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setpgroup(
    attr: *mut posix_spawnattr_t,
    pgroup: pid_t,
) -> c_int {
    let Some(attr) = (unsafe { attr.as_mut() }) else {
        return EINVAL;
    };
    attr.__pgroup = pgroup;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getpgroup(
    attr: *const posix_spawnattr_t,
    pgroup: *mut pid_t,
) -> c_int {
    let (Some(attr), Some(pgroup)) = (unsafe { attr.as_ref() }, unsafe { pgroup.as_mut() }) else {
        return EINVAL;
    };
    *pgroup = attr.__pgroup;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setsigmask(
    attr: *mut posix_spawnattr_t,
    sigmask: *const sigset_t,
) -> c_int {
    let (Some(attr), Some(sigmask)) =
        (unsafe { attr.as_mut() }, unsafe { sigmask.as_ref() })
    else {
        return EINVAL;
    };
    attr.__ss = *sigmask;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getsigmask(
    attr: *const posix_spawnattr_t,
    sigmask: *mut sigset_t,
) -> c_int {
    let (Some(attr), Some(sigmask)) =
        (unsafe { attr.as_ref() }, unsafe { sigmask.as_mut() })
    else {
        return EINVAL;
    };
    *sigmask = attr.__ss;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setsigdefault(
    attr: *mut posix_spawnattr_t,
    sigdefault: *const sigset_t,
) -> c_int {
    let (Some(attr), Some(sigdefault)) =
        (unsafe { attr.as_mut() }, unsafe { sigdefault.as_ref() })
    else {
        return EINVAL;
    };
    attr.__sd = *sigdefault;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getsigdefault(
    attr: *const posix_spawnattr_t,
    sigdefault: *mut sigset_t,
) -> c_int {
    let (Some(attr), Some(sigdefault)) =
        (unsafe { attr.as_ref() }, unsafe { sigdefault.as_mut() })
    else {
        return EINVAL;
    };
    *sigdefault = attr.__sd;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setschedparam(
    attr: *mut posix_spawnattr_t,
    param: *const sched_param,
) -> c_int {
    let (Some(attr), Some(param)) = (unsafe { attr.as_mut() }, unsafe { param.as_ref() }) else {
        return EINVAL;
    };
    attr.__sp = *param;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getschedparam(
    attr: *const posix_spawnattr_t,
    param: *mut sched_param,
) -> c_int {
    let (Some(attr), Some(param)) = (unsafe { attr.as_ref() }, unsafe { param.as_mut() }) else {
        return EINVAL;
    };
    *param = attr.__sp;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_setschedpolicy(
    attr: *mut posix_spawnattr_t,
    policy: c_int,
) -> c_int {
    let Some(attr) = (unsafe { attr.as_mut() }) else {
        return EINVAL;
    };
    attr.__policy = policy;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawnattr_getschedpolicy(
    attr: *const posix_spawnattr_t,
    policy: *mut c_int,
) -> c_int {
    let (Some(attr), Some(policy)) = (unsafe { attr.as_ref() }, unsafe { policy.as_mut() }) else {
        return EINVAL;
    };
    *policy = attr.__policy;
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_init(
    actions: *mut posix_spawn_file_actions_t,
) -> c_int {
    let Some(actions) = (unsafe { actions.as_mut() }) else {
        return EINVAL;
    };

    let vec = Box::new(Vec::<FileAction>::new());
    actions.__actions = Box::into_raw(vec).cast();
    actions.__pad = [0; 15];
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_destroy(
    actions: *mut posix_spawn_file_actions_t,
) -> c_int {
    let Some(actions) = (unsafe { actions.as_mut() }) else {
        return EINVAL;
    };
    if !actions.__actions.is_null() {
        drop(unsafe { Box::from_raw(actions.__actions.cast::<Vec<FileAction>>()) });
        actions.__actions = ptr::null_mut();
    }
    0
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_addopen(
    actions: *mut posix_spawn_file_actions_t,
    fd: c_int,
    path: *const c_char,
    oflag: c_int,
    mode: mode_t,
) -> c_int {
    match file_actions_mut(actions) {
        Ok(actions) => match clone_c_string(path) {
            Ok(path) => {
                actions.push(FileAction::Open {
                    fd,
                    path,
                    oflag,
                    mode,
                });
                0
            }
            Err(Errno(err)) => err,
        },
        Err(Errno(err)) => err,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_addclose(
    actions: *mut posix_spawn_file_actions_t,
    fd: c_int,
) -> c_int {
    match file_actions_mut(actions) {
        Ok(actions) => {
            actions.push(FileAction::Close(fd));
            0
        }
        Err(Errno(err)) => err,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_adddup2(
    actions: *mut posix_spawn_file_actions_t,
    fd: c_int,
    newfd: c_int,
) -> c_int {
    if fd < 0 || newfd < 0 {
        return EBADF;
    }
    match file_actions_mut(actions) {
        Ok(actions) => {
            actions.push(FileAction::Dup2 {
                src: fd,
                dst: newfd,
            });
            0
        }
        Err(Errno(err)) => err,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_addchdir_np(
    actions: *mut posix_spawn_file_actions_t,
    path: *const c_char,
) -> c_int {
    match file_actions_mut(actions) {
        Ok(actions) => match clone_c_string(path) {
            Ok(path) => {
                actions.push(FileAction::Chdir(path));
                0
            }
            Err(Errno(err)) => err,
        },
        Err(Errno(err)) => err,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn posix_spawn_file_actions_addfchdir_np(
    actions: *mut posix_spawn_file_actions_t,
    fd: c_int,
) -> c_int {
    if fd < 0 {
        return EBADF;
    }
    match file_actions_mut(actions) {
        Ok(actions) => {
            actions.push(FileAction::Fchdir(fd));
            0
        }
        Err(Errno(err)) => err,
    }
}
