#ifndef _RELIBC_FLOAT_H
#define _RELIBC_FLOAT_H

#include <sys/types.h>
#include <bits/float.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/float.h.html>.
 */
#define FLT_RADIX 2

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/float.h.html>.
 */
int flt_rounds(void);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_FLOAT_H */
