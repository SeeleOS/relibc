#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#define LOCK_SH 1

#define LOCK_EX 2

#define LOCK_NB 4

#define LOCK_UN 8

#define L_SET 0

#define L_INCR 1

#define L_XTND 2

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://man7.org/linux/man-pages/man2/flock.2.html>.
 */
int flock(int fd, int operation);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_FILE_H */
