#ifndef _RELIBC_UTIME_H
#define _RELIBC_UTIME_H

#include <sys/types.h>
#include <features.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/utime.h.html>.
 */
struct utimbuf {
  time_t actime;
  time_t modtime;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/utime.html>.
 */
__deprecated int utime(const char *filename, const struct utimbuf *times);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_UTIME_H */
