#ifndef _RELIBC_LIMITS_H
#define _RELIBC_LIMITS_H

#define HOST_NAME_MAX 64

#define NAME_MAX 255

#define PASS_MAX 128

#define PATH_MAX 4096

#define NGROUPS_MAX 65536

#define CHAR_BIT 8

#define WORD_BIT 32

#if defined(__ILP32__)
#define LONG_BIT 32
#endif

#if defined(__LP64__)
#define LONG_BIT 64
#endif

#if (defined(__aarch64__) || defined(__riscv))
#define CHAR_MAX 255
#endif

#if !(defined(__aarch64__) || defined(__riscv))
#define CHAR_MAX 127
#endif

#define SCHAR_MAX 127

#define SHRT_MAX 32767

#define INT_MAX 2147483647

#if defined(__ILP32__)
#define LONG_MAX 2147483647
#endif

#if defined(__LP64__)
#define LONG_MAX 9223372036854775807
#endif

#define LLONG_MAX 9223372036854775807

#if defined(__ILP32__)
#define SSIZE_MAX 2147483647
#endif

#if defined(__LP64__)
#define SSIZE_MAX 9223372036854775807
#endif

#define UCHAR_MAX 255

#define USHRT_MAX 65535

#define UINT_MAX 4294967295

#if defined(__ILP32__)
#define ULONG_MAX 4294967295
#endif

#if defined(__LP64__)
#define ULONG_MAX 18446744073709551615ull
#endif

#define ULLONG_MAX 18446744073709551615ull

#if (defined(__aarch64__) || defined(__riscv))
#define CHAR_MIN 0
#endif

#if !(defined(__aarch64__) || defined(__riscv))
#define CHAR_MIN -128
#endif

#define SCHAR_MIN (-SCHAR_MAX - 1)

#define SHRT_MIN (-SHRT_MAX - 1)

#define INT_MIN (-INT_MAX - 1)

#define LONG_MIN (-LONG_MAX - 1)

#define LLONG_MIN (-LLONG_MAX - 1)

#if defined(__linux__)
#define PAGE_SIZE 4096
#endif

#define _POSIX_AIO_LISTIO_MAX 2

#define _POSIX_AIO_MAX 1

#define _POSIX_ARG_MAX 4096

#define _POSIX_CHILD_MAX 25

#define _POSIX_CLOCKRES_MIN 20000000

#define _POSIX_DELAYTIMER_MAX 32

#define _POSIX_HOST_NAME_MAX 255

#define _POSIX_LINK_MAX 8

#define _POSIX_LOGIN_NAME_MAX 9

#define _POSIX_MAX_CANON 255

#define _POSIX_MAX_INPUT 255

#define _POSIX_NAME_MAX 14

#define _POSIX_NGROUPS_MAX 8

#define _POSIX_OPEN_MAX 20

#define _POSIX_PATH_MAX 256

#define _POSIX_PIPE_BUF 512

#define _POSIX_RE_DUP_MAX 255

#define _POSIX_RTSIG_MAX 8

#define _POSIX_SEM_NSEMS_MAX 256

#define _POSIX_SEM_VALUE_MAX 32767

#define _POSIX_SIGQUEUE_MAX 32

#define _POSIX_SSIZE_MAX 32767

#define _POSIX_STREAM_MAX 8

#define _POSIX_SYMLINK_MAX 255

#define _POSIX_SYMLOOP_MAX 8

#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4

#define _POSIX_THREAD_KEYS_MAX 128

#define _POSIX_THREAD_THREADS_MAX 64

#define _POSIX_TIMER_MAX 32

#define _POSIX_TTY_NAME_MAX 9

#define _POSIX_TZNAME_MAX 6

#define _POSIX2_BC_BASE_MAX 99

#define _POSIX2_BC_DIM_MAX 2048

#define _POSIX2_BC_SCALE_MAX 99

#define _POSIX2_BC_STRING_MAX 1000

#define _POSIX2_CHARCLASS_NAME_MAX 14

#define _POSIX2_COLL_WEIGHTS_MAX 2

#define _POSIX2_EXPR_NEST_MAX 32

#define _POSIX2_LINE_MAX 2048

#define _POSIX2_RE_DUP_MAX 255

#define BC_BASE_MAX _POSIX2_BC_BASE_MAX

#define BC_DIM_MAX _POSIX2_BC_DIM_MAX

#define BC_SCALE_MAX _POSIX2_BC_SCALE_MAX

#define BC_STRING_MAX _POSIX2_BC_STRING_MAX

#define CHARCLASS_NAME_MAX _POSIX2_CHARCLASS_NAME_MAX

#define COLL_WEIGHTS_MAX _POSIX2_COLL_WEIGHTS_MAX

#define EXPR_NEST_MAX _POSIX2_EXPR_NEST_MAX

#define LINE_MAX _POSIX2_LINE_MAX

#define RE_DUP_MAX _POSIX2_RE_DUP_MAX

#define PTHREAD_DESTRUCTOR_ITERATIONS _POSIX_THREAD_DESTRUCTOR_ITERATIONS

#define PTHREAD_KEYS_MAX (4096 * 32)

#define PTHREAD_STACK_MIN 65536

#endif  /* _RELIBC_LIMITS_H */
