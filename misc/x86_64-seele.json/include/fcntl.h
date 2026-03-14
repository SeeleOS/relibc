#ifndef _RELIBC_FCNTL_H
#define _RELIBC_FCNTL_H

#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

#define F_DUPFD 0

#define F_GETFD 1

#define F_SETFD 2

#define F_GETFL 3

#define F_SETFL 4

#define F_GETLK 5

#define F_SETLK 6

#define F_SETLKW 7

#define F_OFD_GETLK 36

#define F_OFD_SETLK 37

#define F_OFD_SETLKW 38

#define F_DUPFD_CLOEXEC 1030

#define F_RDLCK 0

#define F_WRLCK 1

#define F_UNLCK 2

#define F_ULOCK 0

#define F_LOCK 1

#define F_TLOCK 2

#define F_TEST 3

#if defined(__linux__)
#define O_RDONLY 0
#endif

#if defined(__redox__)
#define O_RDONLY 65536
#endif

#if defined(__linux__)
#define O_WRONLY 1
#endif

#if defined(__redox__)
#define O_WRONLY 131072
#endif

#if defined(__linux__)
#define O_RDWR 2
#endif

#if defined(__redox__)
#define O_RDWR 196608
#endif

#if defined(__linux__)
#define O_ACCMODE 3
#endif

#if defined(__redox__)
#define O_ACCMODE 196608
#endif

#if defined(__linux__)
#define O_CREAT 64
#endif

#if defined(__redox__)
#define O_CREAT 33554432
#endif

#if defined(__linux__)
#define O_EXCL 128
#endif

#if defined(__redox__)
#define O_EXCL 134217728
#endif

#if defined(__linux__)
#define O_NOCTTY 256
#endif

#if defined(__redox__)
#define O_NOCTTY 512
#endif

#if defined(__linux__)
#define O_TRUNC 512
#endif

#if defined(__redox__)
#define O_TRUNC 67108864
#endif

#if defined(__linux__)
#define O_APPEND 1024
#endif

#if defined(__redox__)
#define O_APPEND 524288
#endif

#if defined(__linux__)
#define O_NONBLOCK 2048
#endif

#if defined(__redox__)
#define O_NONBLOCK 262144
#endif

#if defined(__linux__)
#define O_DIRECTORY 65536
#endif

#if defined(__redox__)
#define O_DIRECTORY 268435456
#endif

#if defined(__linux__)
#define O_NOFOLLOW 131072
#endif

#if defined(__redox__)
#define O_NOFOLLOW -2147483648
#endif

#if defined(__linux__)
#define O_CLOEXEC 524288
#endif

#if defined(__redox__)
#define O_CLOEXEC 16777216
#endif

#if defined(__linux__)
#define O_PATH 2097152
#endif

#if defined(__redox__)
#define O_PATH 536870912
#endif

#if defined(__linux__)
#define FD_CLOEXEC 524288
#endif

#if defined(__redox__)
#define FD_CLOEXEC 16777216
#endif

#if defined(__linux__)
#define O_NDELAY O_NONBLOCK
#endif

#if defined(__redox__)
#define O_NDELAY O_NONBLOCK
#endif

#if defined(__linux__)
#define AT_FDCWD -100
#endif

#if defined(__redox__)
#define AT_FDCWD -100
#endif

#if defined(__linux__)
#define AT_SYMLINK_NOFOLLOW 256
#endif

#if defined(__redox__)
#define AT_SYMLINK_NOFOLLOW 512
#endif

#if defined(__linux__)
#define AT_EACCESS 512
#endif

#if defined(__linux__)
#define AT_REMOVEDIR 512
#endif

#if defined(__redox__)
#define AT_REMOVEDIR 512
#endif

#if defined(__linux__)
#define AT_SYMLINK_FOLLOW 1024
#endif

#if defined(__linux__)
#define AT_EMPTY_PATH 4096
#endif

#if defined(__redox__)
#define AT_EMPTY_PATH 16384
#endif

#if defined(__redox__)
#define O_SHLOCK 1048576
#endif

#if defined(__redox__)
#define O_EXLOCK 2097152
#endif

#if defined(__redox__)
#define O_ASYNC 4194304
#endif

#if defined(__redox__)
#define O_FSYNC 8388608
#endif

#if defined(__redox__)
#define O_SYNC O_FSYNC
#endif

#if defined(__redox__)
#define O_SYMLINK 1073741824
#endif

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/fcntl.h.html>.
 */
struct flock {
  short l_type;
  short l_whence;
  off_t l_start;
  off_t l_len;
  pid_t l_pid;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/creat.html>.
 */
int creat(const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fcntl.html>.
 */
int fcntl(int fildes, int cmd, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/open.html>.
 */
int open(const char *path, int oflag, ...);

void cbindgen_stupid_struct_user_for_fcntl(struct flock);

int posix_fallocate(int fd, off_t offset, off_t length);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_FCNTL_H */
