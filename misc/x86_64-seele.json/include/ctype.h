#ifndef _RELIBC_CTYPE_H
#define _RELIBC_CTYPE_H

#include <bits/ctype.h>
#include <features.h>
#include <bits/locale-t.h> // for locale_t

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isalnum.html>.
 */
int isalnum(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isalnum_l.html>.
 */
int isalnum_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isalpha.html>.
 */
int isalpha(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isalpha_l.html>.
 */
int isalpha_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/isascii.html>.
 *
 * The `isascii()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 7, and removed in Issue 8.
 */
__deprecated int isascii(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isblank.html>.
 */
int isblank(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isblank_l.html>.
 */
int isblank_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/iscntrl.html>.
 */
int iscntrl(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/iscntrl_l.html>.
 */
int iscntrl_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isdigit.html>.
 */
int isdigit(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isdigit_l.html>.
 */
int isdigit_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isgraph.html>.
 */
int isgraph(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isgraph_l.html>.
 */
int isgraph_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/islower.html>.
 */
int islower(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/islower_l.html>.
 */
int islower_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isprint.html>.
 */
int isprint(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isprint_l.html>.
 */
int isprint_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ispunct.html>.
 */
int ispunct(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/ispunct_l.html>.
 */
int ispunct_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isspace.html>.
 */
int isspace(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isspace_l.html>.
 */
int isspace_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isupper.html>.
 */
int isupper(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isupper_l.html>.
 */
int isupper_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isxdigit.html>.
 */
int isxdigit(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/isxdigit_l.html>.
 */
int isxdigit_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/toascii.html>.
 *
 * The `toascii()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 7, and removed in Issue 8.
 */
__deprecated int toascii(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tolower.html>.
 */
int tolower(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tolower_l.html>.
 */
int tolower_l(int c, locale_t _loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/toupper.html>.
 */
int toupper(int c);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/toupper_l.html>.
 */
int toupper_l(int c, locale_t _loc);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_CTYPE_H */
