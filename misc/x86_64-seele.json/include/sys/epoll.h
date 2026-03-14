#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H

#include <signal.h>

#define EPOLL_CTL_ADD 1

#define EPOLL_CTL_DEL 2

#define EPOLL_CTL_MOD 3

#if defined(__linux__)
#define EPOLL_CLOEXEC 524288
#endif

#if defined(__redox__)
#define EPOLL_CLOEXEC 16777216
#endif

#if defined(__linux__)
#define EPOLLIN 1
#endif

#if defined(__redox__)
#define EPOLLIN 1
#endif

#if defined(__linux__)
#define EPOLLPRI 2
#endif

#if defined(__redox__)
#define EPOLLPRI 2
#endif

#if defined(__linux__)
#define EPOLLOUT 4
#endif

#if defined(__redox__)
#define EPOLLOUT 4
#endif

#if defined(__linux__)
#define EPOLLERR 8
#endif

#if defined(__redox__)
#define EPOLLERR 8
#endif

#if defined(__linux__)
#define EPOLLHUP 16
#endif

#if defined(__redox__)
#define EPOLLHUP 16
#endif

#if defined(__linux__)
#define EPOLLNVAL 32
#endif

#if defined(__redox__)
#define EPOLLNVAL 32
#endif

#if defined(__linux__)
#define EPOLLRDNORM 64
#endif

#if defined(__redox__)
#define EPOLLRDNORM 64
#endif

#if defined(__linux__)
#define EPOLLRDBAND 128
#endif

#if defined(__redox__)
#define EPOLLRDBAND 128
#endif

#if defined(__linux__)
#define EPOLLWRNORM 256
#endif

#if defined(__redox__)
#define EPOLLWRNORM 256
#endif

#if defined(__linux__)
#define EPOLLWRBAND 512
#endif

#if defined(__redox__)
#define EPOLLWRBAND 512
#endif

#if defined(__linux__)
#define EPOLLMSG 1024
#endif

#if defined(__redox__)
#define EPOLLMSG 1024
#endif

#if defined(__linux__)
#define EPOLLRDHUP 8192
#endif

#if defined(__redox__)
#define EPOLLRDHUP 8192
#endif

#if defined(__linux__)
#define EPOLLEXCLUSIVE (1 << 28)
#endif

#if defined(__redox__)
#define EPOLLEXCLUSIVE (1 << 28)
#endif

#if defined(__linux__)
#define EPOLLWAKEUP (1 << 29)
#endif

#if defined(__redox__)
#define EPOLLWAKEUP (1 << 29)
#endif

#if defined(__linux__)
#define EPOLLONESHOT (1 << 30)
#endif

#if defined(__redox__)
#define EPOLLONESHOT (1 << 30)
#endif

#if defined(__linux__)
#define EPOLLET (1 << 31)
#endif

#if defined(__redox__)
#define EPOLLET (1 << 31)
#endif

union epoll_data {
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
};

#if (defined(__redox__) && defined(__LP64__))
struct epoll_event {
  uint32_t events;
  union epoll_data data;
  uint64_t _pad;
};
#endif

#if !(defined(__redox__) && defined(__LP64__))
struct epoll_event {
  uint32_t events;
  union epoll_data data;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int epoll_create(int _size);

int epoll_create1(int flags);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

int epoll_pwait(int epfd,
                struct epoll_event *events,
                int maxevents,
                int timeout,
                const sigset_t *sigmask);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_EPOLL_H */
