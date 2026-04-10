#ifndef _STDDEF_H
#define _STDDEF_H
#include <stdint.h>

#define NULL 0

#ifndef __PTRDIFF_TYPE__
#define __PTRDIFF_TYPE__ long int
#endif
typedef __PTRDIFF_TYPE__ ptrdiff_t;

typedef long unsigned int size_t;

#ifndef _WCHAR_T
#define _WCHAR_T
#ifndef __cplusplus
#ifndef __WCHAR_TYPE__
#define __WCHAR_TYPE__ int
#endif
typedef __WCHAR_TYPE__ wchar_t;
#endif
#endif

typedef struct { long long __ll; long double __ld; } max_align_t;

#define offsetof(type, member) __builtin_offsetof(type, member)

#endif /* _STDDEF_H */
