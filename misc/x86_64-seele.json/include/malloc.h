#ifndef _RELIBC_MALLOC_H
#define _RELIBC_MALLOC_H

#include <features.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://man7.org/linux/man-pages/man3/posix_memalign.3.html>.
 */
__deprecated void *pvalloc(size_t size);

/**
 * See <https://man7.org/linux/man-pages/man3/malloc_usable_size.3.html>.
 */
size_t malloc_usable_size(void *ptr);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_MALLOC_H */

#include <bits/malloc.h>
