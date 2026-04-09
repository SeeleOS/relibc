use alloc::boxed::Box;
use seele_sys::{
    abi::time::{TimeType, TimerNotifyStruct, TimerStateStruct, TimerStateType},
    signal::Signal,
    syscalls::{
        misc::{get_current_time, time_since_boot},
        timer::{
            create_timer, delete_timer, get_timer_overrun, get_timer_state, set_timer_state,
        },
    },
    utils::process_result,
};

use super::Sys;
use crate::{
    error::{Errno, Result},
    header::{
        errno::EINVAL,
        signal::{SIGEV_NONE, SIGEV_SIGNAL, sigevent},
        time::{CLOCK_MONOTONIC, CLOCK_REALTIME, NANOSECONDS, TIMER_ABSTIME, itimerspec},
    },
    out::Out,
    platform::{
        sys::e_raw,
        types::{c_int, c_void, clockid_t, timer_t},
    },
};

#[repr(C)]
struct TimerHandle {
    id: u64,
    time_type: TimeType,
}

impl From<TimerStateStruct> for itimerspec {
    fn from(value: TimerStateStruct) -> Self {
        match value.state_type {
            TimerStateType::Disabled => Self::default(),
            TimerStateType::OneShot => Self {
                it_interval: ns_to_timespec(0),
                it_value: ns_to_timespec(value.deadline),
            },
            TimerStateType::Periodic => Self {
                it_interval: ns_to_timespec(value.interval),
                it_value: ns_to_timespec(value.deadline),
            },
        }
    }
}

impl From<itimerspec> for TimerStateStruct {
    fn from(value: itimerspec) -> Self {
        let deadline = timespec_to_ns(&value.it_value);
        let interval = timespec_to_ns(&value.it_interval);

        let state_type = if deadline == 0 {
            TimerStateType::Disabled
        } else if interval == 0 {
            TimerStateType::OneShot
        } else {
            TimerStateType::Periodic
        };

        Self {
            state_type,
            deadline,
            interval,
        }
    }
}

fn ns_to_timespec(nanoseconds: u64) -> crate::header::bits_time::timespec {
    crate::header::bits_time::timespec {
        tv_sec: (nanoseconds / (NANOSECONDS as u64)) as _,
        tv_nsec: (nanoseconds % (NANOSECONDS as u64)) as _,
    }
}

fn timespec_to_ns(value: &crate::header::bits_time::timespec) -> u64 {
    (value.tv_sec as u64)
        .saturating_mul(NANOSECONDS as u64)
        .saturating_add(value.tv_nsec as u64)
}

fn current_time_ns(time_type: TimeType) -> Result<u64> {
    match time_type {
        TimeType::Realtime => e_raw(process_result(get_current_time())).map(|v| v as u64),
        TimeType::SinceBoot => e_raw(process_result(time_since_boot())).map(|v| v as u64),
    }
}

fn timer_state_to_itimerspec(value: TimerStateStruct, time_type: TimeType) -> Result<itimerspec> {
    let now = current_time_ns(time_type)?;

    Ok(match value.state_type {
        TimerStateType::Disabled => itimerspec::default(),
        TimerStateType::OneShot => itimerspec {
            it_interval: ns_to_timespec(0),
            it_value: ns_to_timespec(value.deadline.saturating_sub(now)),
        },
        TimerStateType::Periodic => itimerspec {
            it_interval: ns_to_timespec(value.interval),
            it_value: ns_to_timespec(value.deadline.saturating_sub(now)),
        },
    })
}

fn timer_state_from_itimerspec(
    value: &itimerspec,
    flags: c_int,
    time_type: TimeType,
) -> Result<TimerStateStruct> {
    let mut timer_state = TimerStateStruct::from(value.clone());

    if !matches!(timer_state.state_type, TimerStateType::Disabled) && (flags & TIMER_ABSTIME) == 0
    {
        timer_state.deadline = current_time_ns(time_type)?.saturating_add(timer_state.deadline);
    }

    Ok(timer_state)
}

fn timer_handle(timerid: timer_t) -> &'static mut TimerHandle {
    unsafe { &mut *(timerid as *mut TimerHandle) }
}

fn timer_notify_from_sigevent(evp: &sigevent) -> Result<TimerNotifyStruct> {
    match evp.sigev_notify {
        SIGEV_NONE => Ok(TimerNotifyStruct::default()),
        SIGEV_SIGNAL => Ok(TimerNotifyStruct {
            notify_type: seele_sys::abi::time::TimerNotifyType::Signal,
            signal: Signal::try_from(evp.sigev_signo as u64).map_err(|_| Errno(EINVAL))?,
        }),
        _ => Err(Errno(EINVAL)),
    }
}

impl TryFrom<clockid_t> for TimeType {
    type Error = Errno;
    fn try_from(value: clockid_t) -> core::result::Result<Self, Self::Error> {
        match value {
            CLOCK_MONOTONIC => Ok(TimeType::SinceBoot),
            CLOCK_REALTIME => Ok(TimeType::Realtime),
            _ => Err(Errno(EINVAL)),
        }
    }
}

pub(super) fn timer_create(
    clock_id: clockid_t,
    evp: &sigevent,
    mut timerid: Out<timer_t>,
) -> Result<()> {
    let time_type: TimeType = clock_id.try_into()?;
    let notify_type = timer_notify_from_sigevent(evp)?;

    let timer_id = e_raw(process_result(create_timer(
        time_type,
        &notify_type as *const TimerNotifyStruct,
    )))?;

    if !timerid.as_mut_ptr().is_null() {
        let handle = Box::into_raw(Box::new(TimerHandle { id: timer_id as u64, time_type }));
        unsafe {
            timerid.write(handle as *mut c_void);
        }
    }

    Ok(())
}

pub(super) fn timer_delete(timerid: timer_t) -> Result<()> {
    let handle = timer_handle(timerid);
    e_raw(process_result(delete_timer(handle.id)))?;
    unsafe {
        drop(Box::from_raw(timerid as *mut TimerHandle));
    }
    Ok(())
}

pub(super) fn timer_getoverrun(timerid: timer_t) -> Result<c_int> {
    let handle = timer_handle(timerid);
    e_raw(process_result(get_timer_overrun(handle.id))).map(|v| v as c_int)
}

pub(super) fn timer_gettime(timerid: timer_t, mut value: Out<itimerspec>) -> Result<()> {
    let handle = timer_handle(timerid);
    let mut timer_state = TimerStateStruct::default();

    e_raw(process_result(get_timer_state(
        handle.id,
        &mut timer_state as *mut TimerStateStruct,
    )))?;

    value.write(timer_state_to_itimerspec(timer_state, handle.time_type)?);

    Ok(())
}

pub(super) fn timer_settime(
    timerid: timer_t,
    flags: c_int,
    value: &itimerspec,
    ovalue: Option<Out<itimerspec>>,
) -> Result<()> {
    let handle = timer_handle(timerid);

    if let Some(mut old) = ovalue {
        let mut timer_state = TimerStateStruct::default();
        e_raw(process_result(get_timer_state(
            handle.id,
            &mut timer_state as *mut TimerStateStruct,
        )))?;
        old.write(timer_state_to_itimerspec(timer_state, handle.time_type)?);
    }

    let timer_state = timer_state_from_itimerspec(value, flags, handle.time_type)?;
    e_raw(process_result(set_timer_state(
        handle.id,
        &timer_state as *const TimerStateStruct,
    )))?;

    Ok(())
}
