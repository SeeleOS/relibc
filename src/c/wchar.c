#include <wchar.h>

float wcstof(const wchar_t *ptr, wchar_t **end) {
    return (float)wcstod(ptr, end);
}

long double wcstold(const wchar_t *ptr, wchar_t **end) {
    return (long double)wcstod(ptr, end);
}
