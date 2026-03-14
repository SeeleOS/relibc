#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <bits/sys/select.h>
#include <time.h>
#include <signal.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_select.h.html>.
 *
 */
struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pselect.html>.
 */
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_SELECT_H */
