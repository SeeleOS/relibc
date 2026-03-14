#ifndef _RELIBC_SCHED_H
#define _RELIBC_SCHED_H

#include <sys/types.h>
#include <bits/time.h> // for timespec


/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
 */
#define SCHED_FIFO 0

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
 */
#define SCHED_RR 1

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
 */
#define SCHED_OTHER 2

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html>.
 */
struct sched_param {
  int sched_priority;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sched_yield.html>.
 */
int sched_yield(void);

void cbindgen_stupid_struct_user_for_sched_param(struct sched_param);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_SCHED_H */
