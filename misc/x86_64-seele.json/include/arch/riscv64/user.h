#ifndef _RISCV64_USER_H
#define _RISCV64_USER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct user_regs_struct {
  unsigned long regs[31];
  unsigned long pc;
};

struct user_fpregs_f_struct {
  float fpregs[32];
  unsigned int fcsr;
};

struct user_fpregs_g_struct {
  double fpregs[32];
  unsigned int fcsr;
};

struct user_fpregs_struct {
  struct user_fpregs_f_struct f_regs;
  struct user_fpregs_g_struct g_regs;
};

typedef struct user_regs_struct elf_gregset_t;

typedef unsigned long elf_greg_t;

typedef struct user_fpregs_struct elf_fpregset_t;

void _cbindgen_only_generates_structs_if_they_are_mentioned_which_is_dumb_riscv64_user(struct user_regs_struct a,
                                                                                       struct user_fpregs_struct b,
                                                                                       elf_gregset_t c,
                                                                                       elf_greg_t d,
                                                                                       elf_fpregset_t e);

#endif  /* _RISCV64_USER_H */
