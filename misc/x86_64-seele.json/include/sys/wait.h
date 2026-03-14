#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <sys/types.h>
#include <sys/resource.h>

#define WNOHANG 1

#define WUNTRACED 2

#define WSTOPPED 2

#define WEXITED 4

#define WCONTINUED 8

#define WNOWAIT 16777216

#define __WNOTHREAD 536870912

#define __WALL 1073741824

#define __WCLONE 2147483648

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/wait.html>.
 */
pid_t wait(int *stat_loc);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/waitpid.html>.
 */
pid_t waitpid(pid_t pid, int *stat_loc, int options);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_WAIT_H */

#include <bits/sys/wait.h>
