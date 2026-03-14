#ifndef _RELIBC_BITS_TIME_H
#define _RELIBC_BITS_TIME_H

#include <sys/types.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/time.h.html>.
 */
struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void cbindgen_stupid_alias_timespec(struct timespec);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_BITS_TIME_H */
