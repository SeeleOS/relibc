#ifndef _RELIBC_UNISTD_H
#define _RELIBC_UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <features.h>

#define F_OK 0

#define R_OK 4

#define W_OK 2

#define X_OK 1

#define SEEK_SET 0

#define SEEK_CUR 1

#define SEEK_END 2

#define F_ULOCK 0

#define F_LOCK 1

#define F_TLOCK 2

#define F_TEST 3

#define STDIN_FILENO 0

#define STDOUT_FILENO 1

#define STDERR_FILENO 2

#define L_cuserid 9

#define _CS_PATH 0

#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS 1

#define _CS_POSIX_V5_WIDTH_RESTRICTED_ENVS 4

#define _CS_POSIX_V7_WIDTH_RESTRICTED_ENVS 5

#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS 1116

#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS 1117

#define _CS_POSIX_V6_ILP32_OFF32_LIBS 1118

#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS 1119

#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS 1120

#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS 1121

#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS 1122

#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS 1123

#define _CS_POSIX_V6_LP64_OFF64_CFLAGS 1124

#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS 1125

#define _CS_POSIX_V6_LP64_OFF64_LIBS 1126

#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS 1127

#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS 1128

#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS 1129

#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS 1130

#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS 1131

#define _CS_POSIX_V7_ILP32_OFF32_CFLAGS 1132

#define _CS_POSIX_V7_ILP32_OFF32_LDFLAGS 1133

#define _CS_POSIX_V7_ILP32_OFF32_LIBS 1134

#define _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS 1135

#define _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS 1136

#define _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS 1137

#define _CS_POSIX_V7_ILP32_OFFBIG_LIBS 1138

#define _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS 1139

#define _CS_POSIX_V7_LP64_OFF64_CFLAGS 1140

#define _CS_POSIX_V7_LP64_OFF64_LDFLAGS 1141

#define _CS_POSIX_V7_LP64_OFF64_LIBS 1142

#define _CS_POSIX_V7_LP64_OFF64_LINTFLAGS 1143

#define _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS 1144

#define _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS 1145

#define _CS_POSIX_V7_LPBIG_OFFBIG_LIBS 1146

#define _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS 1147

#define _PC_LINK_MAX 0

#define _PC_MAX_CANON 1

#define _PC_MAX_INPUT 2

#define _PC_NAME_MAX 3

#define _PC_PATH_MAX 4

#define _PC_PIPE_BUF 5

#define _PC_CHOWN_RESTRICTED 6

#define _PC_NO_TRUNC 7

/**
 * Check if file (terminal) supports disabling control chars (CC)
 */
#define _PC_VDISABLE 8

#define _PC_SYNC_IO 9

#define _PC_ASYNC_IO 10

#define _PC_PRIO_IO 11

#define _PC_SOCK_MAXBUF 12

#define _PC_FILESIZEBITS 13

#define _PC_REC_INCR_XFER_SIZE 14

#define _PC_REC_MAX_XFER_SIZE 15

#define _PC_REC_MIN_XFER_SIZE 16

#define _PC_REC_XFER_ALIGN 17

#define _PC_ALLOC_SIZE_MIN 18

#define _PC_SYMLINK_MAX 19

#define _PC_2_SYMLINKS 20

#if defined(__redox__)
#define _SC_ARG_MAX 0
#endif

#if defined(__linux__)
#define _SC_ARG_MAX 0
#endif

#if defined(__redox__)
#define _SC_CHILD_MAX 1
#endif

#if defined(__linux__)
#define _SC_CHILD_MAX 1
#endif

#if defined(__redox__)
#define _SC_CLK_TCK 2
#endif

#if defined(__linux__)
#define _SC_CLK_TCK 2
#endif

#if defined(__redox__)
#define _SC_NGROUPS_MAX 3
#endif

#if defined(__linux__)
#define _SC_NGROUPS_MAX 3
#endif

#if defined(__redox__)
#define _SC_OPEN_MAX 4
#endif

#if defined(__linux__)
#define _SC_OPEN_MAX 4
#endif

#if defined(__redox__)
#define _SC_STREAM_MAX 5
#endif

#if defined(__linux__)
#define _SC_STREAM_MAX 5
#endif

#if defined(__redox__)
#define _SC_TZNAME_MAX 6
#endif

#if defined(__linux__)
#define _SC_TZNAME_MAX 6
#endif

#if defined(__redox__)
#define _SC_VERSION 29
#endif

#if defined(__linux__)
#define _SC_VERSION 29
#endif

#if defined(__redox__)
#define _SC_PAGESIZE 30
#endif

#if defined(__linux__)
#define _SC_PAGESIZE 30
#endif

#if defined(__redox__)
#define _SC_PAGE_SIZE 30
#endif

#if defined(__linux__)
#define _SC_PAGE_SIZE 30
#endif

#if defined(__redox__)
#define _SC_RE_DUP_MAX 44
#endif

#if defined(__linux__)
#define _SC_RE_DUP_MAX 44
#endif

#if defined(__redox__)
#define _SC_NPROCESSORS_CONF 57
#endif

#if defined(__linux__)
#define _SC_NPROCESSORS_CONF 83
#endif

#if defined(__redox__)
#define _SC_NPROCESSORS_ONLN 58
#endif

#if defined(__linux__)
#define _SC_NPROCESSORS_ONLN 84
#endif

#if defined(__redox__)
#define _SC_PHYS_PAGES 59
#endif

#if defined(__linux__)
#define _SC_PHYS_PAGES 85
#endif

#if defined(__redox__)
#define _SC_AVPHYS_PAGES 60
#endif

#if defined(__linux__)
#define _SC_AVPHYS_PAGES 86
#endif

#if defined(__redox__)
#define _SC_GETGR_R_SIZE_MAX 69
#endif

#if defined(__linux__)
#define _SC_GETGR_R_SIZE_MAX 69
#endif

#if defined(__redox__)
#define _SC_GETPW_R_SIZE_MAX 70
#endif

#if defined(__linux__)
#define _SC_GETPW_R_SIZE_MAX 70
#endif

#if defined(__redox__)
#define _SC_LOGIN_NAME_MAX 71
#endif

#if defined(__linux__)
#define _SC_LOGIN_NAME_MAX 71
#endif

#if defined(__redox__)
#define _SC_TTY_NAME_MAX 72
#endif

#if defined(__linux__)
#define _SC_TTY_NAME_MAX 72
#endif

#if defined(__redox__)
#define _SC_SYMLOOP_MAX 173
#endif

#if defined(__linux__)
#define _SC_SYMLOOP_MAX 173
#endif

#if defined(__redox__)
#define _SC_HOST_NAME_MAX 180
#endif

#if defined(__linux__)
#define _SC_HOST_NAME_MAX 180
#endif

#if defined(__redox__)
#define _SC_SIGQUEUE_MAX 190
#endif

#if defined(__linux__)
#define _SC_SIGQUEUE_MAX 34
#endif

#if defined(__redox__)
#define _SC_REALTIME_SIGNALS 191
#endif

#if defined(__linux__)
#define _SC_REALTIME_SIGNALS 9
#endif

#if defined(__linux__)
#define _XOPEN_IOV_MAX 16
#endif

#if defined(__linux__)
#define _XOPEN_NAME_MAX 255
#endif

#if defined(__linux__)
#define _XOPEN_PATH_MAX 1024
#endif

#if defined(__linux__)
#define _SC_JOB_CONTROL 7
#endif

#if defined(__linux__)
#define _SC_SAVED_IDS 8
#endif

#if defined(__linux__)
#define _SC_PRIORITY_SCHEDULING 10
#endif

#if defined(__linux__)
#define _SC_TIMERS 11
#endif

#if defined(__linux__)
#define _SC_ASYNCHRONOUS_IO 12
#endif

#if defined(__linux__)
#define _SC_PRIORITIZED_IO 13
#endif

#if defined(__linux__)
#define _SC_SYNCHRONIZED_IO 14
#endif

#if defined(__linux__)
#define _SC_FSYNC 15
#endif

#if defined(__linux__)
#define _SC_MAPPED_FILES 16
#endif

#if defined(__linux__)
#define _SC_MEMLOCK 17
#endif

#if defined(__linux__)
#define _SC_MEMLOCK_RANGE 18
#endif

#if defined(__linux__)
#define _SC_MEMORY_PROTECTION 19
#endif

#if defined(__linux__)
#define _SC_MESSAGE_PASSING 20
#endif

#if defined(__linux__)
#define _SC_SEMAPHORES 21
#endif

#if defined(__linux__)
#define _SC_SHARED_MEMORY_OBJECTS 22
#endif

#if defined(__linux__)
#define _SC_AIO_LISTIO_MAX 23
#endif

#if defined(__linux__)
#define _SC_AIO_MAX 24
#endif

#if defined(__linux__)
#define _SC_AIO_PRIO_DELTA_MAX 25
#endif

#if defined(__linux__)
#define _SC_DELAYTIMER_MAX 26
#endif

#if defined(__linux__)
#define _SC_MQ_OPEN_MAX 27
#endif

#if defined(__linux__)
#define _SC_MQ_PRIO_MAX 28
#endif

#if defined(__linux__)
#define _SC_RTSIG_MAX 31
#endif

#if defined(__linux__)
#define _SC_SEM_NSEMS_MAX 32
#endif

#if defined(__linux__)
#define _SC_SEM_VALUE_MAX 33
#endif

#if defined(__linux__)
#define _SC_TIMER_MAX 35
#endif

#if defined(__linux__)
#define _SC_BC_BASE_MAX 36
#endif

#if defined(__linux__)
#define _SC_BC_DIM_MAX 37
#endif

#if defined(__linux__)
#define _SC_BC_SCALE_MAX 38
#endif

#if defined(__linux__)
#define _SC_BC_STRING_MAX 39
#endif

#if defined(__linux__)
#define _SC_COLL_WEIGHTS_MAX 40
#endif

#if defined(__linux__)
#define _SC_EXPR_NEST_MAX 42
#endif

#if defined(__linux__)
#define _SC_LINE_MAX 43
#endif

#if defined(__linux__)
#define _SC_2_VERSION 46
#endif

#if defined(__linux__)
#define _SC_2_C_BIND 47
#endif

#if defined(__linux__)
#define _SC_2_C_DEV 48
#endif

#if defined(__linux__)
#define _SC_2_FORT_DEV 49
#endif

#if defined(__linux__)
#define _SC_2_FORT_RUN 50
#endif

#if defined(__linux__)
#define _SC_2_SW_DEV 51
#endif

#if defined(__linux__)
#define _SC_2_LOCALEDEF 52
#endif

#if defined(__linux__)
#define _SC_UIO_MAXIOV 60
#endif

#if defined(__linux__)
#define _SC_IOV_MAX 60
#endif

#if defined(__linux__)
#define _SC_THREADS 67
#endif

#if defined(__linux__)
#define _SC_THREAD_SAFE_FUNCTIONS 68
#endif

#if defined(__linux__)
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 73
#endif

#if defined(__linux__)
#define _SC_THREAD_KEYS_MAX 74
#endif

#if defined(__linux__)
#define _SC_THREAD_STACK_MIN 75
#endif

#if defined(__linux__)
#define _SC_THREAD_THREADS_MAX 76
#endif

#if defined(__linux__)
#define _SC_THREAD_ATTR_STACKADDR 77
#endif

#if defined(__linux__)
#define _SC_THREAD_ATTR_STACKSIZE 78
#endif

#if defined(__linux__)
#define _SC_THREAD_PRIORITY_SCHEDULING 79
#endif

#if defined(__linux__)
#define _SC_THREAD_PRIO_INHERIT 80
#endif

#if defined(__linux__)
#define _SC_THREAD_PRIO_PROTECT 81
#endif

#if defined(__linux__)
#define _SC_THREAD_PROCESS_SHARED 82
#endif

#if defined(__linux__)
#define _SC_ATEXIT_MAX 87
#endif

#if defined(__linux__)
#define _SC_PASS_MAX 88
#endif

#if defined(__linux__)
#define _SC_XOPEN_VERSION 89
#endif

#if defined(__linux__)
#define _SC_XOPEN_XCU_VERSION 90
#endif

#if defined(__linux__)
#define _SC_XOPEN_UNIX 91
#endif

#if defined(__linux__)
#define _SC_XOPEN_CRYPT 92
#endif

#if defined(__linux__)
#define _SC_XOPEN_ENH_I18N 93
#endif

#if defined(__linux__)
#define _SC_XOPEN_SHM 94
#endif

#if defined(__linux__)
#define _SC_2_CHAR_TERM 95
#endif

#if defined(__linux__)
#define _SC_2_UPE 97
#endif

#if defined(__linux__)
#define _SC_XOPEN_XPG2 98
#endif

#if defined(__linux__)
#define _SC_XOPEN_XPG3 99
#endif

#if defined(__linux__)
#define _SC_XOPEN_XPG4 100
#endif

#if defined(__linux__)
#define _SC_NZERO 109
#endif

#if defined(__linux__)
#define _SC_XBS5_ILP32_OFF32 125
#endif

#if defined(__linux__)
#define _SC_XBS5_ILP32_OFFBIG 126
#endif

#if defined(__linux__)
#define _SC_XBS5_LP64_OFF64 127
#endif

#if defined(__linux__)
#define _SC_XBS5_LPBIG_OFFBIG 128
#endif

#if defined(__linux__)
#define _SC_XOPEN_LEGACY 129
#endif

#if defined(__linux__)
#define _SC_XOPEN_REALTIME 130
#endif

#if defined(__linux__)
#define _SC_XOPEN_REALTIME_THREADS 131
#endif

#if defined(__linux__)
#define _SC_ADVISORY_INFO 132
#endif

#if defined(__linux__)
#define _SC_BARRIERS 133
#endif

#if defined(__linux__)
#define _SC_CLOCK_SELECTION 137
#endif

#if defined(__linux__)
#define _SC_CPUTIME 138
#endif

#if defined(__linux__)
#define _SC_THREAD_CPUTIME 139
#endif

#if defined(__linux__)
#define _SC_MONOTONIC_CLOCK 149
#endif

#if defined(__linux__)
#define _SC_READER_WRITER_LOCKS 153
#endif

#if defined(__linux__)
#define _SC_SPIN_LOCKS 154
#endif

#if defined(__linux__)
#define _SC_REGEXP 155
#endif

#if defined(__linux__)
#define _SC_SHELL 157
#endif

#if defined(__linux__)
#define _SC_SPAWN 159
#endif

#if defined(__linux__)
#define _SC_SPORADIC_SERVER 160
#endif

#if defined(__linux__)
#define _SC_THREAD_SPORADIC_SERVER 161
#endif

#if defined(__linux__)
#define _SC_TIMEOUTS 164
#endif

#if defined(__linux__)
#define _SC_TYPED_MEMORY_OBJECTS 165
#endif

#if defined(__linux__)
#define _SC_2_PBS 168
#endif

#if defined(__linux__)
#define _SC_2_PBS_ACCOUNTING 169
#endif

#if defined(__linux__)
#define _SC_2_PBS_LOCATE 170
#endif

#if defined(__linux__)
#define _SC_2_PBS_MESSAGE 171
#endif

#if defined(__linux__)
#define _SC_2_PBS_TRACK 172
#endif

#if defined(__linux__)
#define _SC_STREAMS 174
#endif

#if defined(__linux__)
#define _SC_2_PBS_CHECKPOINT 175
#endif

#if defined(__linux__)
#define _SC_V6_ILP32_OFF32 176
#endif

#if defined(__linux__)
#define _SC_V6_ILP32_OFFBIG 177
#endif

#if defined(__linux__)
#define _SC_V6_LP64_OFF64 178
#endif

#if defined(__linux__)
#define _SC_V6_LPBIG_OFFBIG 179
#endif

#if defined(__linux__)
#define _SC_TRACE 181
#endif

#if defined(__linux__)
#define _SC_TRACE_EVENT_FILTER 182
#endif

#if defined(__linux__)
#define _SC_TRACE_INHERIT 183
#endif

#if defined(__linux__)
#define _SC_TRACE_LOG 184
#endif

#if defined(__linux__)
#define _SC_IPV6 235
#endif

#if defined(__linux__)
#define _SC_RAW_SOCKETS 236
#endif

#if defined(__linux__)
#define _SC_V7_ILP32_OFF32 237
#endif

#if defined(__linux__)
#define _SC_V7_ILP32_OFFBIG 238
#endif

#if defined(__linux__)
#define _SC_V7_LP64_OFF64 239
#endif

#if defined(__linux__)
#define _SC_V7_LPBIG_OFFBIG 240
#endif

#if defined(__linux__)
#define _SC_SS_REPL_MAX 241
#endif

#if defined(__linux__)
#define _SC_TRACE_EVENT_NAME_MAX 242
#endif

#if defined(__linux__)
#define _SC_TRACE_NAME_MAX 243
#endif

#if defined(__linux__)
#define _SC_TRACE_SYS_MAX 244
#endif

#if defined(__linux__)
#define _SC_TRACE_USER_EVENT_MAX 245
#endif

#if defined(__linux__)
#define _SC_XOPEN_STREAMS 246
#endif

#if defined(__linux__)
#define _SC_THREAD_ROBUST_PRIO_INHERIT 247
#endif

#if defined(__linux__)
#define _SC_THREAD_ROBUST_PRIO_PROTECT 248
#endif

#if defined(__linux__)
#define _SC_MINSIGSTKSZ 249
#endif

#if defined(__linux__)
#define _SC_SIGSTKSZ 250
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getopt.html>.
 */
extern char *optarg;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getopt.html>.
 */
extern int opterr;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getopt.html>.
 */
extern int optind;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getopt.html>.
 */
extern int optopt;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fork.html>.
 */
pid_t _Fork(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/_Exit.html>.
 */
void _exit(int status) __noreturn;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/access.html>.
 */
int access(const char *path, int mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/alarm.html>.
 */
unsigned int alarm(unsigned int seconds);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/chdir.html>.
 */
int chdir(const char *path);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/chown.html>.
 */
int chown(const char *path, uid_t owner, gid_t group);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/chroot.html>.
 *
 * # Deprecation
 * The `chroot()` function was marked legacy in the System Interface & Headers
 * Issue 5, and removed in Issue 6.
 */
__deprecated int chroot(const char *path);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/close.html>.
 */
int close(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/confstr.html>.
 */
size_t confstr(int name, char *buf, size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/crypt.html>.
 */
char *crypt(const char *key, const char *salt);

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man3/daemon.3.html>.
 */
int daemon(int nochdir, int noclose);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dup.html>.
 */
int dup(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dup.html>.
 */
int dup2(int fildes, int fildes2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/encrypt.html>.
 *
 * # Deprecation
 * The `encrypt()` function was marked obsolescent in the Open Group Base Specifications Issue 8.
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execl(const char *path, const char *arg0, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execle(const char *path, const char *arg0, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execlp(const char *file, const char *arg0, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execv(const char *path, char *const *argv);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execve(const char *path, char *const *argv, char *const *envp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int fexecve(int fd, char *const *argv, char *const *envp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/exec.html>.
 */
int execvp(const char *file, char *const *argv);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchdir.html>.
 */
int fchdir(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchown.html>.
 */
int fchown(int fildes, uid_t owner, gid_t group);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fdatasync.html>.
 */
int fdatasync(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fork.html>.
 */
pid_t fork(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fsync.html>.
 */
int fsync(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ftruncate.html>.
 */
int ftruncate(int fildes, off_t length);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getcwd.html>.
 */
char *getcwd(char *buf, size_t size);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/getdtablesize.html>.
 *
 * # Deprecation
 * The `getdtablesize()` function was marked legacy in the System Interface &
 * Headers Issue 5, and removed in Issue 6.
 */
__deprecated int getdtablesize(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getegid.html>.
 */
gid_t getegid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/geteuid.html>.
 */
uid_t geteuid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgid.html>.
 */
gid_t getgid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgroups.html>.
 */
int getgroups(int size, gid_t *list);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/gethostname.html>.
 */
int gethostname(char *name, size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getlogin.html>.
 */
char *getlogin(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getlogin.html>.
 */
int getlogin_r(char *name, size_t namesize);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/getpagesize.html>.
 *
 * # Deprecation
 * The `getpagesize()` function was marked legacy in the System Interface &
 * Headers Issue 5, and removed in Issue 6.
 */
__deprecated int getpagesize(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getpgid.html>.
 */
pid_t getpgid(pid_t pid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getpgrp.html>.
 */
pid_t getpgrp(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getpid.html>.
 */
pid_t getpid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getppid.html>.
 */
pid_t getppid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getresgid.html>.
 */
int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getresuid.html>.
 */
int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getsid.html>.
 */
pid_t getsid(pid_t pid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getuid.html>.
 */
uid_t getuid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/getwd.html>.
 *
 * # Deprecation
 * The `getwd()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated char *getwd(char *path_name);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isatty.html>.
 */
int isatty(int fd);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/lchown.html>.
 */
int lchown(const char *path, uid_t owner, gid_t group);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/link.html>.
 */
int link(const char *path1, const char *path2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/lockf.html>.
 */
int lockf(int fildes, int function, off_t size);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/lseek.html>.
 */
off_t lseek(int fildes, off_t offset, int whence);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pause.html>.
 */
int pause(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pipe.html>.
 */
int pipe(int *fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pipe.html>.
 */
int pipe2(int *fildes, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/posix_close.html>.
 */
int posix_close(int fildes, int flag);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/read.html>.
 */
ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/write.html>.
 */
ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/read.html>.
 */
ssize_t read(int fildes, void *buf, size_t nbyte);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/readlink.html>.
 */
ssize_t readlink(const char *path, char *buf, size_t bufsize);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/readlink.html>.
 */
ssize_t readlinkat(int dirfd, const char *pathname, char *buf, size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/rmdir.html>.
 */
int rmdir(const char *path);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setegid.html>.
 */
int setegid(gid_t gid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/seteuid.html>.
 */
int seteuid(uid_t uid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setgid.html>.
 */
int setgid(gid_t gid);

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man2/setgroups.2.html>.
 *
 * TODO: specified in `grp.h`?
 */
int setgroups(size_t size, const gid_t *list);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setpgid.html>.
 */
int setpgid(pid_t pid, pid_t pgid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/setpgrp.html>.
 *
 * # Deprecation
 * The `setpgrp()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 7, and removed in Issue 8.
 */
__deprecated pid_t setpgrp(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setregid.html>.
 */
int setregid(gid_t rgid, gid_t egid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setresgid.html>.
 */
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setresuid.html>.
 */
int setresuid(uid_t ruid, uid_t euid, uid_t suid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setreuid.html>.
 */
int setreuid(uid_t ruid, uid_t euid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setsid.html>.
 */
pid_t setsid(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setuid.html>.
 */
int setuid(uid_t uid);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sleep.html>.
 */
unsigned int sleep(unsigned int seconds);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/swab.html>.
 */
void swab(const void *src, void *dest, ssize_t nbytes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/symlink.html>.
 */
int symlink(const char *path1, const char *path2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sync.html>.
 */
void sync(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetpgrp.html>.
 */
pid_t tcgetpgrp(int fd);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsetpgrp.html>.
 */
int tcsetpgrp(int fd, pid_t pgrp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/truncate.html>.
 */
int truncate(const char *path, off_t length);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ttyname.html>.
 */
char *ttyname(int fildes);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ttyname.html>.
 */
int ttyname_r(int fildes, char *name, size_t namesize);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/ualarm.html>.
 *
 * # Deprecation
 * The `ualarm()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated useconds_t ualarm(useconds_t usecs, useconds_t interval);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/unlink.html>.
 */
int unlink(const char *path);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/usleep.html>.
 *
 * # Deprecation
 * The `usleep()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated int usleep(useconds_t useconds);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/write.html>.
 */
ssize_t write(int fildes, const void *buf, size_t nbyte);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/brk.html>.
 *
 * # Deprecation
 * The `brk()` function was marked legacy in the System Interface & Headers
 * Issue 5, and removed in Issue 6.
 */
__deprecated int brk(void *addr);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/brk.html>.
 *
 * # Deprecation
 * The `sbrk()` function was marked legacy in the System Interface & Headers
 * Issue 5, and removed in Issue 6.
 */
__deprecated void *sbrk(intptr_t incr);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getopt.html>.
 */
int getopt(int argc, char *const *argv, const char *optstring);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xsh/getpass.html>.
 *
 * # Deprecation
 * The `getpass()` function was marked legacy in the Open Group System
 * Interface & Headers Issue 5, and removed in Issue 6.
 */
__deprecated char *getpass(const char *prompt);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fpathconf.html>.
 */
long fpathconf(int _fildes, int name);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fpathconf.html>.
 */
long pathconf(const char *_path, int name);

long sysconf(int name);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_UNISTD_H */

#include <bits/unistd.h>
