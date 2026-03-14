#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H

#define UTSLENGTH 65

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_utsname.h.html>.
 */
struct utsname {
  char sysname[UTSLENGTH];
  char nodename[UTSLENGTH];
  char release[UTSLENGTH];
  char version[UTSLENGTH];
  char machine[UTSLENGTH];
  char domainname[UTSLENGTH];
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/uname.html>.
 */
int uname(struct utsname *uts);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_UTSNAME_H */
