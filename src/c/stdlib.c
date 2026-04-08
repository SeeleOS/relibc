double strtod(const char *nptr, char **endptr);
typedef void *locale_t;

long double strtold(const char *nptr, char **endptr) {
    return (long double)strtod(nptr, endptr);
}

long double strtold_l(const char *nptr, char **endptr, locale_t loc) {
    (void)loc;
    return strtold(nptr, endptr);
}

double relibc_ldtod(const long double* val) {
    return (double)(*val);
}

void relibc_dtold(double val, long double* out) {
    *out = (long double)val;
}
