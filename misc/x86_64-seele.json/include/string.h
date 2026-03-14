#ifndef _RELIBC_STRING_H
#define _RELIBC_STRING_H

#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <bits/locale-t.h> // for locale_t


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memccpy.html>.
 *
 * # Safety
 * The caller must ensure that:
 * - `n` is not longer than the memory area pointed to by `s1`, and
 * - `n` is not longer than the memory area pointed to by `s2`.
 */
void *memccpy(void *s1, const void *s2, int c, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memchr.html>.
 */
void *memchr(const void *haystack, int needle, size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memcmp.html>.
 */
int memcmp(const void *s1, const void *s2, uintptr_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memcpy.html>.
 *
 * # Safety
 * The caller must ensure that *either*:
 * - `n` is 0, *or*
 *     - `s1` is convertible to a `&mut [MaybeUninit<u8>]` with length `n`,
 *       and
 *     - `s2` is convertible to a `&[MaybeUninit<u8>]` with length `n`.
 */
void *memcpy(void *s1, const void *s2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memmem.html>.
 *
 * # Safety
 * The caller must ensure that:
 * - `haystack` is convertible to a `&[u8]` with length `haystacklen`, and
 * - `needle` is convertible to a `&[u8]` with length `needlelen`.
 */
void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memmove.html>.
 */
void *memmove(void *s1, const void *s2, size_t n);

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man3/memchr.3.html>.
 */
void *memrchr(const void *haystack, int needle, size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/memset.html>.
 */
void *memset(void *s, int c, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcpy.html>.
 */
char *stpcpy(char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strncpy.html>.
 */
char *stpncpy(char *s1, const char *s2, size_t n);

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man3/strstr.3.html>.
 */
char *strcasestr(const char *haystack, const char *needle);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcat.html>.
 */
char *strcat(char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strchr.html>.
 *
 * # Safety
 * The caller is required to ensure that `s` is a valid pointer to a buffer
 * containing at least one nul value. The pointed-to buffer must not be
 * modified for the duration of the call.
 */
char *strchr(const char *s, int c);

/**
 * Non-POSIX, see <https://man7.org/linux/man-pages/man3/strchr.3.html>.
 */
char *strchrnul(const char *s, int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcmp.html>.
 */
int strcmp(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcoll_l.html>.
 */
int strcoll_l(const char *s1, const char *s2, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcoll.html>.
 */
int strcoll(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcpy.html>.
 */
char *strcpy(char *dst, const char *src);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strcspn.html>.
 */
size_t strcspn(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strdup.html>.
 */
char *strdup(const char *s1);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strerror_l.html>.
 */
char *strerror_l(int errnum, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strerror.html>.
 */
char *strerror(int errnum);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strerror_r.html>.
 */
int strerror_r(int errnum, char *buf, size_t buflen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strlcat.html>.
 */
size_t strlcat(char *dst, const char *src, size_t dstsize);

char *strsep(char **str_, const char *sep);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strlcat.html>.
 */
size_t strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strlen.html>.
 */
size_t strlen(const char *s);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strncat.html>.
 */
char *strncat(char *s1, const char *s2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strncmp.html>.
 */
int strncmp(const char *s1, const char *s2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strncpy.html>.
 */
char *strncpy(char *s1, const char *s2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strdup.html>.
 */
char *strndup(const char *s1, size_t size);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strlen.html>.
 */
size_t strnlen(const char *s, size_t size);

/**
 * Non-POSIX, see <https://en.cppreference.com/w/c/string/byte/strlen>.
 */
size_t strnlen_s(const char *s, size_t size);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strpbrk.html>.
 */
char *strpbrk(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strrchr.html>.
 */
char *strrchr(const char *s, int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strsignal.html>.
 */
char *strsignal(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strspn.html>.
 */
size_t strspn(const char *s1, const char *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strstr.html>.
 */
char *strstr(const char *haystack, const char *needle);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strtok.html>.
 */
char *strtok(char *s1, const char *delimiter);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strtok.html>.
 */
char *strtok_r(char *s, const char *delimiter, char **lasts);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strxfrm_l.html>.
 */
size_t strxfrm_l(char *s1, const char *s2, size_t n, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/strxfrm.html>.
 */
size_t strxfrm(char *s1, const char *s2, size_t n);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_STRING_H */
