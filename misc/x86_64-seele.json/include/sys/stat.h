#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <sys/types.h>
#include <bits/time.h> // for timespec
#include <bits/sys/stat.h>


#define S_IFMT 61440

#define S_IFDIR 16384

#define S_IFCHR 8192

#define S_IFBLK 24576

#define S_IFREG 32768

#define S_IFIFO 4096

#define S_IFLNK 40960

#define S_IFSOCK 49152

#define S_IRWXU 448

#define S_IRUSR 256

#define S_IWUSR 128

#define S_IXUSR 64

#define S_IREAD S_IRUSR

#define S_IWRITE S_IWUSR

#define S_IEXEC S_IXUSR

#define S_IRWXG 56

#define S_IRGRP 32

#define S_IWGRP 16

#define S_IXGRP 8

#define S_IRWXO 7

#define S_IROTH 4

#define S_IWOTH 2

#define S_IXOTH 1

#define S_ISUID 2048

#define S_ISGID 1024

#define S_ISVTX 512

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_stat.h.html>.
 */
struct stat {
  dev_t st_dev;
  ino_t st_ino;
  nlink_t st_nlink;
  mode_t st_mode;
  uid_t st_uid;
  gid_t st_gid;
  dev_t st_rdev;
  off_t st_size;
  blksize_t st_blksize;
  blkcnt_t st_blocks;
  struct timespec st_atim;
  struct timespec st_mtim;
  struct timespec st_ctim;
  char _pad[24];
};

#define UTIME_NOW ((1 << 30) - 1)

#define UTIME_OMIT ((1 << 30) - 2)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/chmod.html>.
 */
int chmod(const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchmod.html>.
 */
int fchmod(int fildes, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchmodat.html>.
 */
int fchmodat(int dirfd, const char *path, mode_t mode, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fstat.html>.
 */
int fstat(int fildes, struct stat *buf);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fstatat.html>.
 */
int fstatat(int fildes, const char *path, struct stat *buf, int flags);

int __fxstat(int _ver, int fildes, struct stat *buf);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/futimens.html>.
 */
int futimens(int fd, const struct timespec *times);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/lstat.html>.
 */
int lstat(const char *path, struct stat *buf);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mkdirat.html>.
 */
int mkdirat(int dirfd, const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mkdir.html>.
 */
int mkdir(const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mkfifoat.html>.
 */
int mkfifoat(int dirfd, const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mkfifo.html>.
 */
int mkfifo(const char *path, mode_t mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mknod.html>.
 */
int mknod(const char *path, mode_t mode, dev_t dev);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mknodat.html>.
 */
int mknodat(int dirfd, const char *path, mode_t mode, dev_t dev);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/stat.html>.
 */
int stat(const char *file, struct stat *buf);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/umask.html>.
 */
mode_t umask(mode_t mask);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_STAT_H */
