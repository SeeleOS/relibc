#ifndef _SYS_PTRACE_H
#define _SYS_PTRACE_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define PTRACE_TRACEME 0

#define PTRACE_PEEKTEXT 1

#define PTRACE_PEEKDATA 2

#define PTRACE_POKETEXT 4

#define PTRACE_POKEDATA 5

#define PTRACE_CONT 7

#define PTRACE_KILL 8

#define PTRACE_SINGLESTEP 9

#define PTRACE_GETREGS 12

#define PTRACE_SETREGS 13

#define PTRACE_GETFPREGS 14

#define PTRACE_SETFPREGS 15

#define PTRACE_ATTACH 16

#define PTRACE_DETACH 17

#define PTRACE_SYSCALL 24

#define PTRACE_SYSEMU 31

#define PTRACE_SYSEMU_SINGLESTEP 32

int ptrace(int request, ...);

#endif  /* _SYS_PTRACE_H */

#include <bits/sys/ptrace.h>
