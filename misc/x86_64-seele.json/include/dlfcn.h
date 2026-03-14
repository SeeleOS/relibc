#ifndef _RELIBC_DLFCN_H
#define _RELIBC_DLFCN_H

#define RTLD_LAZY (1 << 0)

#define RTLD_NOW (1 << 1)

#define RTLD_NOLOAD (1 << 2)

#define RTLD_GLOBAL (1 << 8)

#define RTLD_LOCAL 0

#define RTLD_DEFAULT (void*)0

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/dlfcn.h.html>.
 */
typedef struct {
  const char *dli_fname;
  void *dli_fbase;
  const char *dli_sname;
  void *dli_saddr;
} Dl_info_t;

/**
 * alias as per spec update: https://www.austingroupbugs.net/view.php?id=1847
 */
typedef Dl_info_t Dl_info;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dladdr.html>.
 */
int dladdr(const void *_addr, Dl_info_t *info);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dlopen.html>.
 */
void *dlopen(const char *cfilename, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dlsym.html>.
 */
void *dlsym(void *handle, const char *symbol);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dlclose.html>.
 */
int dlclose(void *handle);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/dlerror.html>.
 */
char *dlerror(void);

void cbindgen_stupid_alias_dlinfo_for_dladdr(Dl_info);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_DLFCN_H */
