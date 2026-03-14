#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#include <sys/types.h>
#include <stdint.h>
#include <sys/time.h>

#define RLIM_INFINITY 18446744073709551615ull

#define RLIM_SAVED_CUR RLIM_INFINITY

#define RLIM_SAVED_MAX RLIM_INFINITY

#define RLIMIT_CPU 0

#define RLIMIT_FSIZE 1

#define RLIMIT_DATA 2

#define RLIMIT_STACK 3

#define RLIMIT_CORE 4

#define RLIMIT_RSS 5

#define RLIMIT_NPROC 6

#define RLIMIT_NOFILE 7

#define RLIMIT_MEMLOCK 8

#define RLIMIT_AS 9

#define RLIMIT_LOCKS 10

#define RLIMIT_SIGPENDING 11

#define RLIMIT_MSGQUEUE 12

#define RLIMIT_NICE 13

#define RLIMIT_RTPRIO 14

#define RLIMIT_NLIMITS 15

#define PRIO_PROCESS 0

#define PRIO_PGRP 1

#define PRIO_USER 2

typedef uint64_t rlim_t;

struct rlimit {
  rlim_t rlim_cur;
  rlim_t rlim_max;
};

struct rusage {
  struct timeval ru_utime;
  struct timeval ru_stime;
  long ru_maxrss;
  long ru_ixrss;
  long ru_idrss;
  long ru_isrss;
  long ru_minflt;
  long ru_majflt;
  long ru_nswap;
  long ru_inblock;
  long ru_oublock;
  long ru_msgsnd;
  long ru_msgrcv;
  long ru_nsignals;
  long ru_nvcsw;
  long ru_nivcsw;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getpriority.html>.
 */
int getpriority(int which, id_t who);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setpriority.html>.
 */
int setpriority(int which, id_t who, int nice);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getrlimit.html>.
 */
int getrlimit(int resource, struct rlimit *rlp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setrlimit.html>.
 */
int setrlimit(int resource, const struct rlimit *rlp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getrusage.html>.
 */
int getrusage(int who, struct rusage *r_usage);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_RESOURCE_H */

#include <bits/sys/resource.h>
