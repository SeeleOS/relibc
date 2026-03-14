#ifndef _RELIBC_DIRENT_H
#define _RELIBC_DIRENT_H

#include <sys/types.h>
#include <features.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/dirent.h.html>.
 */
typedef struct DIR DIR;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/dirent.h.html>.
 */
typedef struct dirent {
  ino_t d_ino;
  off_t d_off;
  unsigned short d_reclen;
  unsigned char d_type;
  char d_name[256];
} dirent;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/dirent.h.html>.
 * must have the same struct layout as dirent
 */
typedef struct posix_dent {
  ino_t d_ino;
  off_t d_off;
  reclen_t d_reclen;
  unsigned char d_type;
  char d_name[256];
} posix_dent;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/alphasort.html>.
 */
int alphasort(const struct dirent **first, const struct dirent **second);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/closedir.html>.
 */
int closedir(struct DIR *dir);

/**
 * See <https://man.freebsd.org/cgi/man.cgi?query=fdopendir&sektion=3>
 *
 * FreeBSD extension that transfers ownership of the directory file descriptor to the user.
 *
 * It doesn't matter if DIR was opened with [`opendir`] or [`fdopendir`].
 */
int fdclosedir(struct DIR *dir);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dirfd.html>.
 */
int dirfd(struct DIR *dir);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fdopendir.html>.
 */
struct DIR *opendir(const char *path);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fdopendir.html>.
 */
struct DIR *fdopendir(int fd);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/posix_getdents.html>.
 */
ssize_t posix_getdents(int fildes, void *buf, size_t nbyte, int _flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/readdir.html>.
 */
struct dirent *readdir(struct DIR *dir);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/rewinddir.html>.
 */
void rewinddir(struct DIR *dir);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/alphasort.html>.
 */
int scandir(const char *dirp,
            struct dirent ***namelist,
            int (*filter)(const struct dirent *_),
            int (*compare)(const struct dirent **_, const struct dirent **_1));

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/seekdir.html>.
 */
void seekdir(struct DIR *dir, long off);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/telldir.html>.
 */
long telldir(struct DIR *dir);

void cbindgen_stupid_struct_user_for_posix_dent(struct posix_dent);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_DIRENT_H */

#include <bits/dirent.h>
