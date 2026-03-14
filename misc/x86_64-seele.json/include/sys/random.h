#ifndef _SYS_RANDOM_H
#define _SYS_RANDOM_H

#include <sys/types.h>

/**
 * See <https://www.man7.org/linux/man-pages/man2/getrandom.2.html>.
 */
#define GRND_NONBLOCK 1

/**
 * See <https://www.man7.org/linux/man-pages/man2/getrandom.2.html>.
 */
#define GRND_RANDOM 2

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://www.man7.org/linux/man-pages/man2/getrandom.2.html>.
 */
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_RANDOM_H */
