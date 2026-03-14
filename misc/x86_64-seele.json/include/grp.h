#ifndef _RELIBC_GRP_H
#define _RELIBC_GRP_H

#include <sys/types.h>
#include <stdint.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/grp.h.html>.
 */
struct group {
  char *gr_name;
  char *gr_passwd;
  gid_t gr_gid;
  char **gr_mem;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * MT-Unsafe race:grgid locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgrgid.html>.
 */
struct group *getgrgid(gid_t gid);

/**
 * MT-Unsafe race:grnam locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgrnam.html>.
 */
struct group *getgrnam(const char *name);

/**
 * MT-Safe locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgrgid_r.html>.
 */
int getgrgid_r(gid_t gid,
               struct group *result_buf,
               char *buffer,
               uintptr_t buflen,
               struct group **result);

/**
 * MT-Safe locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getgrnam_r.html>.
 */
int getgrnam_r(const char *name,
               struct group *result_buf,
               char *buffer,
               uintptr_t buflen,
               struct group **result);

/**
 * MT-Unsafe race:grent race:grentbuf locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endgrent.html>.
 */
struct group *getgrent(void);

/**
 * MT-Unsafe race:grent locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endgrent.html>.
 */
void endgrent(void);

/**
 * MT-Unsafe race:grent locale
 *
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endgrent.html>.
 */
void setgrent(void);

/**
 * MT-Safe locale
 * Not POSIX
 *
 * See <https://www.man7.org/linux/man-pages/man3/getgrouplist.3.html>.
 */
int getgrouplist(const char *user, gid_t group, gid_t *groups, int *ngroups);

/**
 * MT-Safe locale
 * Not POSIX
 *
 * See <https://www.man7.org/linux/man-pages/man3/initgroups.3.html>.
 */
int initgroups(const char *user, gid_t gid);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_GRP_H */
