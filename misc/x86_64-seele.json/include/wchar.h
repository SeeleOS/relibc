#ifndef _RELIBC_WCHAR_H
#define _RELIBC_WCHAR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <bits/wchar.h>
#include <features.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/wchar.h.html>.
 */
typedef struct {

} mbstate_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/btowc.html>.
 */
wint_t btowc(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fgetwc.html>.
 */
wint_t fgetwc(FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fgetws.html>.
 */
wchar_t *fgetws(wchar_t *ws, int n, FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fputwc.html>.
 */
wint_t fputwc(wchar_t wc, FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fputws.html>.
 */
int fputws(const wchar_t *ws, FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwide.html>.
 */
int fwide(FILE *stream, int mode);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwscanf.html>.
 */
int fwscanf(FILE *stream, const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getwc.html>.
 */
wint_t getwc(FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getwchar.html>.
 */
wint_t getwchar(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mbsinit.html>.
 */
int mbsinit(const mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mbrlen.html>.
 */
size_t mbrlen(const char *s, size_t n, mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mbrtowc.html>.
 *
 * Only works for UTF8 at the moment.
 */
size_t mbrtowc(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mbsnrtowcs.html>.
 *
 * Convert a multibyte string to a wide string with a limited amount of bytes.
 */
size_t mbsnrtowcs(wchar_t *dst_ptr,
                  const char **src_ptr,
                  size_t src_len,
                  size_t dst_len,
                  mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/mbsrtowcs.html>.
 *
 * Convert a multibyte string to a wide string.
 */
size_t mbsrtowcs(wchar_t *dst, const char **src, size_t len, mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/putwc.html>.
 */
wint_t putwc(wchar_t wc, FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/putwchar.html>.
 */
wint_t putwchar(wchar_t wc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vswscanf.html>.
 */
int vswscanf(const wchar_t *s, const wchar_t *format, va_list __valist);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwscanf.html>.
 */
int swscanf(const wchar_t *s, const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ungetwc.html>.
 *
 * Push wide character `wc` back onto `stream` so it'll be read next
 */
wint_t ungetwc(wint_t wc, FILE *stream);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vfwprintf.html>.
 */
int vfwprintf(FILE *stream, const wchar_t *format, va_list arg);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwprintf.html>.
 */
int fwprintf(FILE *stream, const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vfwprintf.html>.
 */
int vwprintf(const wchar_t *format, va_list arg);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwprintf.html>.
 */
int wprintf(const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vfwprintf.html>.
 */
int vswprintf(wchar_t *s, size_t n, const wchar_t *format, va_list arg);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwprintf.html>.
 */
int swprintf(wchar_t *s, size_t n, const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcpcpy.html>.
 */
wchar_t *wcpcpy(wchar_t *d, const wchar_t *s);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcpncpy.html>.
 */
wchar_t *wcpncpy(wchar_t *d, const wchar_t *s, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcrtomb.html>.
 *
 * widechar to multibyte.
 */
size_t wcrtomb(char *s, wchar_t wc, mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsdup.html>.
 */
wchar_t *wcsdup(const wchar_t *s);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsrtombs.html>.
 */
size_t wcsrtombs(char *s, const wchar_t **ws, size_t n, mbstate_t *st);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscat.html>.
 */
wchar_t *wcscat(wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcschr.html>.
 *
 * # Safety
 * The caller is required to ensure that `ws` is a valid pointer to a buffer
 * containing at least one nul value. The pointed-to buffer must not be
 * modified for the duration of the call.
 */
wchar_t *wcschr(const wchar_t *ws, wchar_t wc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscmp.html>.
 */
int wcscmp(const wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscoll.html>.
 */
int wcscoll(const wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscpy.html>.
 */
wchar_t *wcscpy(wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscspn.html>.
 */
size_t wcscspn(const wchar_t *wcs, const wchar_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsftime.html>.
 */
size_t wcsftime(wchar_t *wcs, size_t maxsize, const wchar_t *format, const struct tm *timptr);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcslen.html>.
 */
size_t wcslen(const wchar_t *ws);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsncat.html>.
 */
wchar_t *wcsncat(wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsncmp.html>.
 */
int wcsncmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsncpy.html>.
 */
wchar_t *wcsncpy(wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsnlen.html>.
 */
size_t wcsnlen(const wchar_t *s, size_t maxlen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsnrtombs.html>.
 */
size_t wcsnrtombs(char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcspbrk.html>.
 */
wchar_t *wcspbrk(const wchar_t *wcs, const wchar_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsrchr.html>.
 */
wchar_t *wcsrchr(const wchar_t *ws1, wchar_t wc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsspn.html>.
 */
size_t wcsspn(const wchar_t *wcs, const wchar_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsstr.html>.
 */
wchar_t *wcsstr(const wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstod.html>.
 */
double wcstod(const wchar_t *ptr, wchar_t **end);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstok.html>.
 */
wchar_t *wcstok(wchar_t *wcs, const wchar_t *delim, wchar_t **state);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstol.html>.
 */
long wcstol(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstoll.html>.
 */
long long wcstoll(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstoimax.html>.
 */
intmax_t wcstoimax(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstoul.html>.
 */
unsigned long wcstoul(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstoull.html>.
 */
unsigned long long wcstoull(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcstoimax.html>.
 */
uintmax_t wcstoumax(const wchar_t *ptr, wchar_t **end, int base);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009604499/functions/wcswcs.html>.
 *
 * Marked legacy in issue 6.
 * Encouraged to use `wcsstr` instead, which this implementation simply forwards to.
 */
wchar_t *wcswcs(const wchar_t *ws1, const wchar_t *ws2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcswidth.html>.
 */
int wcswidth(const wchar_t *pwcs, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsxfrm.html>.
 */
size_t wcsxfrm(wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wctob.html>.
 */
int wctob(wint_t c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcwidth.html>.
 */
int wcwidth(wchar_t wc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wmemchr.html>.
 */
wchar_t *wmemchr(const wchar_t *ws, wchar_t wc, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wmemcmp.html>.
 */
int wmemcmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wmemcpy.html>.
 */
wchar_t *wmemcpy(wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wmemmove.html>.
 */
wchar_t *wmemmove(wchar_t *ws1, const wchar_t *ws2, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wmemset.html>.
 */
wchar_t *wmemset(wchar_t *ws, wchar_t wc, size_t n);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vfwscanf.html>.
 */
int vfwscanf(FILE *stream, const wchar_t *format, va_list __valist);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/vwscanf.html>.
 */
int vwscanf(const wchar_t *format, va_list __valist);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wscanf.html>.
 */
int wscanf(const wchar_t *format, ...);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcscasecmp.html>.
 */
int wcscasecmp(const wchar_t *s1, const wchar_t *s2);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wcsncasecmp.html>.
 */
int wcsncasecmp(const wchar_t *s1, const wchar_t *s2, size_t n);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_WCHAR_H */
