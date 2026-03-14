#ifndef _RELIBC_SHADOW_H
#define _RELIBC_SHADOW_H

#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>

struct spwd {
  char *sp_namp;
  char *sp_pwdp;
  long sp_lstchg;
  long sp_min;
  long sp_max;
  long sp_warn;
  long sp_inact;
  long sp_expire;
  unsigned long sp_flag;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct spwd *getspnam(const char *name);

int getspnam_r(const char *name,
               struct spwd *result_buf,
               char *buffer,
               size_t buflen,
               struct spwd **result);

void setspent(void);

void endspent(void);

struct spwd *getspent(void);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_SHADOW_H */
