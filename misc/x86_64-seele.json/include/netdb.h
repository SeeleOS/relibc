#ifndef _RELIBC_NETDB_H
#define _RELIBC_NETDB_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <features.h>

#define AI_PASSIVE 1

#define AI_CANONNAME 2

#define AI_NUMERICHOST 4

#define AI_V4MAPPED 8

#define AI_ALL 16

#define AI_ADDRCONFIG 32

#define AI_NUMERICSERV 1024

#define EAI_BADFLAGS -1

#define EAI_NONAME -2

#define EAI_AGAIN -3

#define EAI_FAIL -4

#define EAI_NODATA -5

#define EAI_FAMILY -6

#define EAI_SOCKTYPE -7

#define EAI_SERVICE -8

#define EAI_ADDRFAMILY -9

#define EAI_MEMORY -10

#define EAI_SYSTEM -11

#define EAI_OVERFLOW -12

#define NI_MAXHOST 1025

#define NI_MAXSERV 32

#define NI_NUMERICHOST 1

#define NI_NUMERICSERV 2

#define NI_NOFQDN 4

#define NI_NAMEREQD 8

#define NI_DGRAM 16

#define HOST_NOT_FOUND 1

#define NO_DATA 2

#define NO_RECOVERY 3

#define TRY_AGAIN 4

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netdb.h.html>.
 */
struct hostent {
  char *h_name;
  char **h_aliases;
  int h_addrtype;
  int h_length;
  char **h_addr_list;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netdb.h.html>.
 */
struct netent {
  char *n_name;
  char **n_aliases;
  int n_addrtype;
  unsigned long n_net;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netdb.h.html>.
 */
struct protoent {
  char *p_name;
  char **p_aliases;
  int p_proto;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netdb.h.html>.
 */
struct servent {
  char *s_name;
  char **s_aliases;
  int s_port;
  char *s_proto;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netdb.h.html>.
 */
struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  socklen_t ai_addrlen;
  char *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endnetent.html>.
 */
void endnetent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endprotoent.html>.
 */
void endprotoent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endservent.html>.
 */
void endservent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009696799/functions/gethostbyaddr.html>.
 * Resolve a host name from a given network address.
 *
 * # Arguments
 * * `v` - Address to resolve as a non-null [`in_addr`]
 * * `length` -
 * * `format` - AF_INET or AF_INET6
 *
 * # Safety
 * * `v` must be a valid pointer.
 * * `length` must correctly match the size of `v` as expected by `format` (usually 4 or 16).
 * * This function is not reentrant and may modify static data.
 *
 * # Panics
 * Panics if `v` is a null pointer.
 *
 * # Deprecation
 * Deprecated as of POSIX.1-2001 and removed in POSIX.1-2008.
 * New code should use [`getaddrinfo`] instead.
 */
__deprecated struct hostent *gethostbyaddr(const void *v, socklen_t length, int format);

/**
 * See <https://pubs.opengroup.org/onlinepubs/009696799/functions/gethostbyaddr.html>.
 * Resolve host information by name or IP address.
 *
 * # Arguments
 * * `name` - Host name or IP address.
 *
 * # Safety
 * `name` must be a valid string.
 * This function is not reentrant and may modify static data.
 *
 * # Panics
 * Panics if `name` is a null pointer.
 *
 * # Deprecation
 * Deprecated as of POSIX.1-2001 and removed in POSIX.1-2008.
 * New code should use [`getaddrinfo`] instead.
 */
__deprecated struct hostent *gethostbyname(const char *name);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endnetent.html>.
 */
struct netent *getnetbyname(const char *name);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endnetent.html>.
 */
struct netent *getnetent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endprotoent.html>.
 */
struct protoent *getprotobyname(const char *name);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endprotoent.html>.
 */
struct protoent *getprotobynumber(int number);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endprotoent.html>.
 */
struct protoent *getprotoent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endservent.html>.
 */
struct servent *getservbyname(const char *name, const char *proto);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endservent.html>.
 */
struct servent *getservbyport(int port, const char *proto);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endservent.html>.
 */
struct servent *getservent(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endnetent.html>.
 */
void setnetent(int stayopen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endprotoent.html>.
 */
void setprotoent(int stayopen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/endservent.html>.
 */
void setservent(int stayopen);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/freeaddrinfo.html>.
 */
int getaddrinfo(const char *node,
                const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getnameinfo.html>.
 */
int getnameinfo(const struct sockaddr *addr,
                socklen_t addrlen,
                char *host,
                socklen_t hostlen,
                char *serv,
                socklen_t servlen,
                int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/freeaddrinfo.html>.
 */
void freeaddrinfo(struct addrinfo *res);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/gai_strerror.html>.
 */
const char *gai_strerror(int errcode);

/**
 * Provide a pointer to relibc's internal [`H_ERRNO`].
 */
__deprecated int *__h_errno_location(void);

__deprecated const char *hstrerror(int errcode);

/**
 * Print error message associated with [`H_ERRNO`] to stderr.
 *
 * # Arguments
 * * `prefix` - An optional prefix to prepend to the error message. May be null or an empty
 * (`""`) C string.
 *
 * # Safety
 * Like [`crate::header::stdio::perror`], `prefix` should be a valid, NUL terminated C string if
 * used. The caller may safely call this function with a null pointer.
 *
 * # Deprecation
 * [`H_ERRNO`], [`hstrerror`], [`herror`], and other functions are deprecated as of
 * POSIX.1-2001 and removed as of POSIX.1-2008. These functions are provided for backwards
 * compatibility but should not be used by new code.
 */
__deprecated void herror(const char *prefix);

void endhostent(void);

void sethostent(int stayopen);

struct hostent *gethostent(void);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_NETDB_H */

#include <bits/netdb.h>
