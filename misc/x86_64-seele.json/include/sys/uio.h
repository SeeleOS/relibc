#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <sys/types.h>

#define IOV_MAX 1024

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_uio.h.html>.
 */
struct iovec {
  void *iov_base;
  size_t iov_len;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Non-POSIX, see <https://man7.org/linux/man-pages/man2/readv.2.html>.
 */
ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);

/**
 * Non-POSIX, see <https://man7.org/linux/man-pages/man2/readv.2.html>.
 */
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/readv.html>.
 */
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/writev.html>.
 */
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_UIO_H */
