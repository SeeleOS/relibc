#ifndef _RELIBC_STRINGS_H
#define _RELIBC_STRINGS_H

#include <features.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/bcmp.html>.
 *
 * # Deprecation
 * The `bcmp()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated int bcmp(const void *first, const void *second, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/bcopy.html>.
 *
 * # Deprecation
 * The `bcopy()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated void bcopy(const void *src, void *dst, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/bzero.html>.
 *
 * # Deprecation
 * The `bzero()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated void bzero(void *dst, size_t n);

/**
 * Non-POSIX, see <https://man7.org/linux/man-pages/man3/bzero.3.html>.
 */
void explicit_bzero(void *s, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ffs.html>.
 */
int ffs(int i);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ffs.html>.
 */
int ffsl(long i);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ffs.html>.
 */
int ffsll(long long i);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/index.html>.
 *
 * # Deprecation
 * The `index()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated char *index(const char *s, int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009695399/functions/rindex.html>.
 *
 * # Deprecation
 * The `rindex()` function was marked legacy in the Open Group Base
 * Specifications Issue 6, and removed in Issue 7.
 */
__deprecated char *rindex(const char *s, int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcasecmp.html>.
 */
int strcasecmp(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcasecmp.html>.
 */
int strncasecmp(const char *s1, const char *s2, size_t n);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_STRINGS_H */
