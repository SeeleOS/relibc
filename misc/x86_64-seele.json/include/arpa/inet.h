#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <inttypes.h>
#include <netinet/in.h>
#include <features.h>
#include <bits/socklen-t.h> // for socklen_t


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/inet_addr.html>.
 *
 * # Deprecated
 * The `inet_addr()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 8.
 */
__deprecated in_addr_t inet_addr(const char *cp);

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man3/inet_aton.3.html>.
 */
int inet_aton(const char *cp, struct in_addr *inp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xns/inet_lnaof.html>.
 *
 * # Deprecation
 * The `inet_lnaof()` function was specified in Networking Services Issue 5,
 * but not in the Open Group Base Specifications Issue 6 and later.
 */
__deprecated in_addr_t inet_lnaof(struct in_addr in);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xns/inet_makeaddr.html>.
 *
 * # Deprecation
 * The `inet_makeaddr()` function was specified in Networking Services Issue
 * 5, but not in the Open Group Base Specifications Issue 6 and later.
 */
__deprecated struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xns/inet_netof.html>.
 *
 * # Deprecation
 * The `inet_netof()` function was specified in Networking Services Issue 5,
 * but not in the Open Group Base Specifications Issue 6 and later.
 */
__deprecated in_addr_t inet_netof(struct in_addr in);

/**
 * See <https://pubs.opengroup.org/onlinepubs/7908799/xns/inet_network.html>.
 *
 * # Deprecation
 * The `inet_network()` function was specified in Networking Services Issue 5,
 * but not in the Open Group Base Specifications Issue 6 and later.
 */
__deprecated in_addr_t inet_network(const char *cp);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/inet_addr.html>.
 *
 * # Deprecation
 * The `inet_ntoa()` function was marked obsolescent in the Open Group Base
 * Specifications Issue 8.
 */
__deprecated char *inet_ntoa(struct in_addr in);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/inet_ntop.html>.
 */
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/inet_ntop.html>.
 */
int inet_pton(int af, const char *src, void *dst);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _ARPA_INET_H */
