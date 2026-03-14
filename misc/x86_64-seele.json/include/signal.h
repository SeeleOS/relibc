#ifndef _RELIBC_SIGNAL_H
#define _RELIBC_SIGNAL_H

#include <bits/signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <bits/pthread.h>
#include <features.h>
#include <bits/time.h> // for timespec
#include <bits/signal.h>


#define SIG_BLOCK 0

#define SIG_UNBLOCK 1

#define SIG_SETMASK 2

#define SIGEV_SIGNAL 0

#define SIGEV_NONE 1

#define SIGEV_THREAD 2

#if defined(__linux__)
#define SIGHUP 1
#endif

#if defined(__redox__)
#define SIGHUP 1
#endif

#if defined(__linux__)
#define SIGINT 2
#endif

#if defined(__redox__)
#define SIGINT 2
#endif

#if defined(__linux__)
#define SIGQUIT 3
#endif

#if defined(__redox__)
#define SIGQUIT 3
#endif

#if defined(__linux__)
#define SIGILL 4
#endif

#if defined(__redox__)
#define SIGILL 4
#endif

#if defined(__linux__)
#define SIGTRAP 5
#endif

#if defined(__redox__)
#define SIGTRAP 5
#endif

#if defined(__linux__)
#define SIGABRT 6
#endif

#if defined(__redox__)
#define SIGABRT 6
#endif

#if defined(__linux__)
#define SIGIOT SIGABRT
#endif

#if defined(__linux__)
#define SIGBUS 7
#endif

#if defined(__redox__)
#define SIGBUS 7
#endif

#if defined(__linux__)
#define SIGFPE 8
#endif

#if defined(__redox__)
#define SIGFPE 8
#endif

#if defined(__linux__)
#define SIGKILL 9
#endif

#if defined(__redox__)
#define SIGKILL 9
#endif

#if defined(__linux__)
#define SIGUSR1 10
#endif

#if defined(__redox__)
#define SIGUSR1 10
#endif

#if defined(__linux__)
#define SIGSEGV 11
#endif

#if defined(__redox__)
#define SIGSEGV 11
#endif

#if defined(__linux__)
#define SIGUSR2 12
#endif

#if defined(__redox__)
#define SIGUSR2 12
#endif

#if defined(__linux__)
#define SIGPIPE 13
#endif

#if defined(__redox__)
#define SIGPIPE 13
#endif

#if defined(__linux__)
#define SIGALRM 14
#endif

#if defined(__redox__)
#define SIGALRM 14
#endif

#if defined(__linux__)
#define SIGTERM 15
#endif

#if defined(__redox__)
#define SIGTERM 15
#endif

#if defined(__linux__)
#define SIGSTKFLT 16
#endif

#if defined(__redox__)
#define SIGSTKFLT 16
#endif

#if defined(__linux__)
#define SIGCHLD 17
#endif

#if defined(__redox__)
#define SIGCHLD 17
#endif

#if defined(__linux__)
#define SIGCONT 18
#endif

#if defined(__redox__)
#define SIGCONT 18
#endif

#if defined(__linux__)
#define SIGSTOP 19
#endif

#if defined(__redox__)
#define SIGSTOP 19
#endif

#if defined(__linux__)
#define SIGTSTP 20
#endif

#if defined(__redox__)
#define SIGTSTP 20
#endif

#if defined(__linux__)
#define SIGTTIN 21
#endif

#if defined(__redox__)
#define SIGTTIN 21
#endif

#if defined(__linux__)
#define SIGTTOU 22
#endif

#if defined(__redox__)
#define SIGTTOU 22
#endif

#if defined(__linux__)
#define SIGURG 23
#endif

#if defined(__redox__)
#define SIGURG 23
#endif

#if defined(__linux__)
#define SIGXCPU 24
#endif

#if defined(__redox__)
#define SIGXCPU 24
#endif

#if defined(__linux__)
#define SIGXFSZ 25
#endif

#if defined(__redox__)
#define SIGXFSZ 25
#endif

#if defined(__linux__)
#define SIGVTALRM 26
#endif

#if defined(__redox__)
#define SIGVTALRM 26
#endif

#if defined(__linux__)
#define SIGPROF 27
#endif

#if defined(__redox__)
#define SIGPROF 27
#endif

#if defined(__linux__)
#define SIGWINCH 28
#endif

#if defined(__redox__)
#define SIGWINCH 28
#endif

#if defined(__linux__)
#define SIGIO 29
#endif

#if defined(__redox__)
#define SIGIO 29
#endif

#if defined(__linux__)
#define SIGPOLL SIGIO
#endif

#if defined(__linux__)
#define SIGPWR 30
#endif

#if defined(__redox__)
#define SIGPWR 30
#endif

#if defined(__linux__)
#define SIGSYS 31
#endif

#if defined(__redox__)
#define SIGSYS 31
#endif

#if defined(__linux__)
#define SIGUNUSED SIGSYS
#endif

#if defined(__linux__)
#define NSIG 32
#endif

#if defined(__redox__)
#define NSIG 32
#endif

#if defined(__linux__)
#define SIGRTMIN 35
#endif

#if defined(__redox__)
#define SIGRTMIN 35
#endif

#if defined(__linux__)
#define SIGRTMAX 64
#endif

#if defined(__redox__)
#define SIGRTMAX 64
#endif

#if defined(__linux__)
#define SA_NOCLDSTOP 1
#endif

#if defined(__redox__)
#define SA_NOCLDSTOP 1073741824
#endif

#if defined(__linux__)
#define SA_NOCLDWAIT 2
#endif

#if defined(__redox__)
#define SA_NOCLDWAIT 2
#endif

#if defined(__linux__)
#define SA_SIGINFO 4
#endif

#if defined(__redox__)
#define SA_SIGINFO 33554432
#endif

#if defined(__linux__)
#define SA_ONSTACK 134217728
#endif

#if defined(__redox__)
#define SA_ONSTACK 67108864
#endif

#if defined(__linux__)
#define SA_RESTART 268435456
#endif

#if defined(__redox__)
#define SA_RESTART 134217728
#endif

#if defined(__linux__)
#define SA_NODEFER 1073741824
#endif

#if defined(__redox__)
#define SA_NODEFER 268435456
#endif

#if defined(__linux__)
#define SA_RESETHAND 2147483648
#endif

#if defined(__redox__)
#define SA_RESETHAND 536870912
#endif

#if defined(__linux__)
#define SA_RESTORER 67108864
#endif

#if defined(__redox__)
#define SA_RESTORER 4
#endif

#if defined(__linux__)
#define SS_ONSTACK 1
#endif

#if defined(__redox__)
#define SS_ONSTACK 1
#endif

#if defined(__linux__)
#define SS_DISABLE 2
#endif

#if defined(__redox__)
#define SS_DISABLE 2
#endif

#if defined(__linux__)
#define MINSIGSTKSZ 2048
#endif

#if defined(__redox__)
#define MINSIGSTKSZ 2048
#endif

#if defined(__linux__)
#define SIGSTKSZ 8096
#endif

#if defined(__redox__)
#define SIGSTKSZ 8096
#endif

#if defined(__linux__)
#define SI_QUEUE -1
#endif

#if defined(__redox__)
#define SI_QUEUE -1
#endif

#if defined(__linux__)
#define SI_USER 0
#endif

#if defined(__redox__)
#define SI_USER 0
#endif

#if defined(__linux__)
#define SI_TIMER 1
#endif

#if defined(__redox__)
#define SI_TIMER 1
#endif

#if defined(__linux__)
#define SI_ASYNCIO 2
#endif

#if defined(__redox__)
#define SI_ASYNCIO 2
#endif

#if defined(__linux__)
#define SI_MESGQ 3
#endif

#if defined(__redox__)
#define SI_MESGQ 3
#endif

#if defined(__linux__)
#define ILL_ILLOPC 1
#endif

#if defined(__redox__)
#define ILL_ILLOPC 1
#endif

#if defined(__linux__)
#define ILL_ILLOPN 2
#endif

#if defined(__redox__)
#define ILL_ILLOPN 2
#endif

#if defined(__linux__)
#define ILL_ILLADR 3
#endif

#if defined(__redox__)
#define ILL_ILLADR 3
#endif

#if defined(__linux__)
#define ILL_ILLTRP 4
#endif

#if defined(__redox__)
#define ILL_ILLTRP 4
#endif

#if defined(__linux__)
#define ILL_PRVOPC 5
#endif

#if defined(__redox__)
#define ILL_PRVOPC 5
#endif

#if defined(__linux__)
#define ILL_PRVREG 6
#endif

#if defined(__redox__)
#define ILL_PRVREG 6
#endif

#if defined(__linux__)
#define ILL_COPROC 7
#endif

#if defined(__redox__)
#define ILL_COPROC 7
#endif

#if defined(__linux__)
#define ILL_BADSTK 8
#endif

#if defined(__redox__)
#define ILL_BADSTK 8
#endif

#if defined(__linux__)
#define FPE_INTDIV 1
#endif

#if defined(__redox__)
#define FPE_INTDIV 1
#endif

#if defined(__linux__)
#define FPE_INTOVF 2
#endif

#if defined(__redox__)
#define FPE_INTOVF 2
#endif

#if defined(__linux__)
#define FPE_FLTDIV 3
#endif

#if defined(__redox__)
#define FPE_FLTDIV 3
#endif

#if defined(__linux__)
#define FPE_FLTOVF 4
#endif

#if defined(__redox__)
#define FPE_FLTOVF 4
#endif

#if defined(__linux__)
#define FPE_FLTUND 5
#endif

#if defined(__redox__)
#define FPE_FLTUND 5
#endif

#if defined(__linux__)
#define FPE_FLTRES 6
#endif

#if defined(__redox__)
#define FPE_FLTRES 6
#endif

#if defined(__linux__)
#define FPE_FLTINV 7
#endif

#if defined(__redox__)
#define FPE_FLTINV 7
#endif

#if defined(__linux__)
#define FPE_FLTSUB 8
#endif

#if defined(__redox__)
#define FPE_FLTSUB 8
#endif

#if defined(__linux__)
#define SEGV_MAPERR 1
#endif

#if defined(__redox__)
#define SEGV_MAPERR 1
#endif

#if defined(__linux__)
#define SEGV_ACCERR 2
#endif

#if defined(__redox__)
#define SEGV_ACCERR 2
#endif

#if defined(__linux__)
#define BUS_ADRALN 1
#endif

#if defined(__redox__)
#define BUS_ADRALN 1
#endif

#if defined(__linux__)
#define BUS_ADRERR 2
#endif

#if defined(__redox__)
#define BUS_ADRERR 2
#endif

#if defined(__linux__)
#define BUS_OBJERR 3
#endif

#if defined(__redox__)
#define BUS_OBJERR 3
#endif

#if defined(__linux__)
#define TRAP_BRKPT 1
#endif

#if defined(__redox__)
#define TRAP_BRKPT 1
#endif

#if defined(__linux__)
#define TRAP_TRACE 2
#endif

#if defined(__redox__)
#define TRAP_TRACE 2
#endif

#if defined(__linux__)
#define CLD_EXITED 1
#endif

#if defined(__redox__)
#define CLD_EXITED 1
#endif

#if defined(__linux__)
#define CLD_KILLED 2
#endif

#if defined(__redox__)
#define CLD_KILLED 2
#endif

#if defined(__linux__)
#define CLD_DUMPED 3
#endif

#if defined(__redox__)
#define CLD_DUMPED 3
#endif

#if defined(__linux__)
#define CLD_TRAPPED 4
#endif

#if defined(__redox__)
#define CLD_TRAPPED 4
#endif

#if defined(__linux__)
#define CLD_STOPPED 5
#endif

#if defined(__redox__)
#define CLD_STOPPED 5
#endif

#if defined(__linux__)
#define CLD_CONTINUED 6
#endif

#if defined(__redox__)
#define CLD_CONTINUED 6
#endif

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/signal.h.html>.
 */
union sigval {
  int sival_int;
  void *sival_ptr;
};

struct siginfo {
  int si_signo;
  int si_errno;
  int si_code;
  pid_t si_pid;
  uid_t si_uid;
  void *si_addr;
  int si_status;
  union sigval si_value;
};

struct sigaltstack {
  void *ss_sp;
  int ss_flags;
  size_t ss_size;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/signal.h.html>
 */
typedef struct sigaltstack stack_t;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/signal.h.html>.
 */
struct sigevent {
  union sigval sigev_value;
  int sigev_signo;
  int sigev_notify;
  void (*sigev_notify_function)(union sigval);
  pthread_attr_t *sigev_notify_attributes;
};

#if defined(__linux__)
struct _libc_fpxreg {
  uint16_t significand[4];
  uint16_t exponent;
  uint16_t __private[3];
};
#endif

#if defined(__linux__)
struct _libc_xmmreg {
  uint32_t element[4];
};
#endif

#if defined(__linux__)
struct _libc_fpstate {
  uint16_t cwd;
  uint16_t swd;
  uint16_t ftw;
  uint16_t fop;
  uint64_t rip;
  uint64_t rdp;
  uint32_t mxcsr;
  uint32_t mxcr_mask;
  struct _libc_fpxreg _st[8];
  struct _libc_xmmreg _xmm[16];
  uint64_t __private[12];
};
#endif

#if defined(__linux__)
struct mcontext {
  int64_t gregs[23];
  struct _libc_fpstate *fpregs;
  uint64_t __private[8];
};
#endif

#if (defined(__redox__) && defined(__i386__))
struct mcontext {
  uint8_t _opaque[512];
};
#endif

#if (defined(__redox__) && defined(__x86_64__))
struct mcontext {
  uint64_t ymm_upper[16][2];
  uint64_t fxsave[29][2];
  uintptr_t r15;
  uintptr_t r14;
  uintptr_t r13;
  uintptr_t r12;
  uintptr_t rbp;
  uintptr_t rbx;
  uintptr_t r11;
  uintptr_t r10;
  uintptr_t r9;
  uintptr_t r8;
  uintptr_t rax;
  uintptr_t rcx;
  uintptr_t rdx;
  uintptr_t rsi;
  uintptr_t rdi;
  uintptr_t rflags;
  uintptr_t rip;
  uintptr_t rsp;
};
#endif

#if (defined(__redox__) && defined(__aarch64__))
struct mcontext {
  uint8_t _opaque[272];
};
#endif

#if (defined(__redox__) && defined(__riscv))
struct mcontext {
  uint8_t _opaque[520];
};
#endif

#if defined(__linux__)
typedef struct mcontext mcontext_t;
#endif

#if defined(__redox__)
typedef struct mcontext mcontext_t;
#endif

#if defined(__linux__)
struct ucontext {
  unsigned long uc_flags;
  ucontext_t *uc_link;
  stack_t uc_stack;
  mcontext_t uc_mcontext;
  sigset_t uc_sigmask;
  uint8_t __private[512];
};
#endif

#if defined(__redox__)
struct ucontext {
#if (defined(__x86_64__) || defined(__aarch64__) || defined(__riscv))
  uintptr_t _pad[1]
#endif
  ;
#if defined(__i386__)
  uintptr_t _pad[3]
#endif
  ;
  ucontext_t *uc_link;
  stack_t uc_stack;
  sigset_t uc_sigmask;
  uintptr_t _sival;
  uint32_t _sigcode;
  uint32_t _signum;
  mcontext_t uc_mcontext;
};
#endif

#if defined(__linux__)
typedef struct ucontext ucontext_t;
#endif

#if defined(__redox__)
typedef struct ucontext ucontext_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void _cbindgen_export_siginfo(struct siginfo a);

extern int32_t sigsetjmp(uint64_t *jb, int32_t savemask);

int32_t __sigsetjmp_tail(uint64_t *jb, int32_t ret);

void siglongjmp(uint64_t *jb, int32_t ret);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/kill.html>.
 */
int kill(pid_t pid, int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigqueue.html>.
 */
int sigqueue(pid_t pid, int sig, union sigval val);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/killpg.html>.
 */
int killpg(pid_t pgrp, int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pthread_kill.html>.
 */
int pthread_kill(pthread_t thread, int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/pthread_sigmask.html>.
 */
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/raise.html>.
 */
int raise(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigaction.html>.
 */
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigaddset.html>.
 */
int sigaddset(sigset_t *set, int signo);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigaltstack.html>.
 */
int sigaltstack(const stack_t *ss, stack_t *old_ss);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigdelset.html>.
 */
int sigdelset(sigset_t *set, int signo);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigemptyset.html>.
 */
int sigemptyset(sigset_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigfillset.html>.
 */
int sigfillset(sigset_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html>.
 *
 * Present in issue 7. Removed in issue 8.
 *
 * Use of this function is unspecified in a multi-threaded process.
 */
int sighold(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html>.
 *
 * Present in issue 7. Removed in issue 8.
 *
 * Use of this function is unspecified in a multi-threaded process.
 */
int sigignore(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/siginterrupt.html>.
 *
 * Marked obsolescent in issue 7. Removed in issue 8.
 */
int siginterrupt(int sig, int flag);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigismember.html>.
 */
int sigismember(const sigset_t *set, int signo);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/signal.html>.
 */
void (*signal(int sig, void (*func)(int)))(int);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html>.
 *
 * Present in issue 7. Removed in issue 8.
 *
 * Use of this function is unspecified in a multi-threaded process.
 */
int sigpause(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigpending.html>.
 */
int sigpending(sigset_t *set);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigprocmask.html>.
 */
int sigprocmask(int how, const sigset_t *set, sigset_t *oset);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html>.
 *
 * Present in issue 7. Removed in issue 8.
 *
 * Use of this function is unspecified in a multi-threaded process.
 */
int sigrelse(int sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html>.
 *
 * Present in issue 7. Removed in issue 8.
 *
 * Use of this function is unspecified in a multi-threaded process.
 */
void (*sigset(int sig, void (*func)(int)))(int);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigsuspend.html>.
 */
int sigsuspend(const sigset_t *sigmask);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigwait.html>.
 */
int sigwait(const sigset_t *set, int *sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigtimedwait.html>.
 */
int sigtimedwait(const sigset_t *set, struct siginfo *sig, const struct timespec *tp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigwaitinfo.html>.
 */
int sigwaitinfo(const sigset_t *set, siginfo_t *sig);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/psignal.html>.
 */
void psignal(int sig, const char *prefix);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/psiginfo.html>.
 */
void psiginfo(const siginfo_t *info, const char *prefix);

void cbindgen_stupid_struct_sigevent_for_timer(struct sigevent);

#if defined(__redox__)
void __completely_unused_cbindgen_workaround_fn_ucontext_mcontext(const ucontext_t *a,
                                                                  const mcontext_t *b);
#endif

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_SIGNAL_H */
