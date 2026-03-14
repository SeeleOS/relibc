#ifndef _RELIBC_FNMATCH_H
#define _RELIBC_FNMATCH_H

#define FNM_NOMATCH 1

#define FNM_NOESCAPE 1

#define FNM_PATHNAME 2

#define FNM_PERIOD 4

#define FNM_CASEFOLD 8

#define FNM_IGNORECASE FNM_CASEFOLD

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/fnmatch.html>.
 */
int fnmatch(const char *pattern, const char *input, int flags);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_FNMATCH_H */
