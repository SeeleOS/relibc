#ifndef _RELIBC_POLL_H
#define _RELIBC_POLL_H

#include <signal.h>
#include <bits/time.h> // for timespec


#define POLLIN 1

#define POLLPRI 2

#define POLLOUT 4

#define POLLERR 8

#define POLLHUP 16

#define POLLNVAL 32

#define POLLRDNORM 64

#define POLLRDBAND 128

#define POLLWRNORM 256

#define POLLWRBAND 512

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/poll.h.html>.
 */
struct pollfd {
  int fd;
  short events;
  short revents;
};

typedef unsigned long nfds_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/poll.html>.
 */
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ppoll.html>.
 */
int ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *tmo_p, const sigset_t *sigmask);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_POLL_H */
