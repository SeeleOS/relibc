#ifndef _AARCH64_USER_H
#define _AARCH64_USER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct user_regs_struct {
  unsigned long long regs[31];
  unsigned long long sp;
  unsigned long long pc;
  unsigned long long pstate;
};

struct user_fpsimd_struct {
  double vregs[32];
  unsigned int fpsr;
  unsigned int fpcr;
};

typedef unsigned long (*elf_gregset_t)[34];

typedef unsigned long elf_greg_t;

typedef struct user_fpsimd_struct elf_fpregset_t;

void _cbindgen_export_aarch64_user(struct user_regs_struct a,
                                   struct user_fpsimd_struct b,
                                   elf_gregset_t c,
                                   elf_greg_t d,
                                   elf_fpregset_t e);

#endif  /* _AARCH64_USER_H */
