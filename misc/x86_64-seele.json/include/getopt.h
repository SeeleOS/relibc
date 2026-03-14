#ifndef _RELIBC_GETOPT_H
#define _RELIBC_GETOPT_H

#include <unistd.h>

#define no_argument 0

#define required_argument 1

#define optional_argument 2

struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://www.man7.org/linux/man-pages/man3/getopt.3.html>.
 *
 * Non-POSIX.
 *
 * Functions the same as `getopt` but also accepts long options.
 */
int getopt_long(int argc,
                char *const *argv,
                const char *optstring,
                const struct option *longopts,
                int *longindex);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_GETOPT_H */
