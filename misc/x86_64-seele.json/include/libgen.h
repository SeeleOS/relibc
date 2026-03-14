#ifndef _RELIBC_LIBGEN_H
#define _RELIBC_LIBGEN_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/basename.html>.
 */
char *basename(char *str);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dirname.html>.
 */
char *dirname(char *str);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_LIBGEN_H */
