#ifndef _NETINET_IN_H
#define _NETINET_IN_H

#include <sys/types.h>
#include <sys/socket.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define INET_ADDRSTRLEN 16

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define INET6_ADDRSTRLEN 46

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_TOS 1

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_RECVTOS 13

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_IP 0

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_ICMP 1

/**
 * Non-POSIX.
 */
#define IPPROTO_IGMP 2

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_TCP 6

/**
 * Non-POSIX.
 */
#define IPPROTO_PUP 12

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_UDP 17

/**
 * Non-POSIX.
 */
#define IPPROTO_IDP 22

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_IPV6 41

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPPROTO_RAW 255

/**
 * Non-POSIX.
 */
#define IPPROTO_MAX 255

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_TTL 2

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPV6_UNICAST_HOPS 16

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPV6_MULTICAST_IF 17

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPV6_MULTICAST_HOPS 18

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPV6_MULTICAST_LOOP 19

/**
 * Non-POSIX.
 */
#define IPV6_ADD_MEMBERSHIP 20

#define IPV6_JOIN_GROUP 20

/**
 * Non-POSIX.
 */
#define IPV6_DROP_MEMBERSHIP 21

#define IPV6_LEAVE_GROUP 21

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define IPV6_V6ONLY 26

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_MULTICAST_IF 32

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_MULTICAST_TTL 33

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_MULTICAST_LOOP 34

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_ADD_MEMBERSHIP 35

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define IP_DROP_MEMBERSHIP 36

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define INADDR_ANY 0

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
#define INADDR_BROADCAST 4294967295

/**
 * Non-POSIX.
 */
#define INADDR_NONE 4294967295

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
#define INADDR_LOOPBACK 2130706433

/**
 * Non-POSIX.
 */
#define INADDR_UNSPEC_GROUP 3758096384

/**
 * Non-POSIX.
 */
#define INADDR_ALLHOSTS_GROUP 3758096385

/**
 * Non-POSIX.
 */
#define INADDR_ALLRTRS_GROUP 3758096386

/**
 * Non-POSIX.
 */
#define INADDR_MAX_LOCAL_GROUP 3758096639

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
struct in6_addr {
  uint8_t s6_addr[16];
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
typedef uint16_t in_port_t;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
struct sockaddr_in6 {
  sa_family_t sin6_family;
  in_port_t sin6_port;
  uint32_t sin6_flowinfo;
  struct in6_addr sin6_addr;
  uint32_t sin6_scope_id;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
typedef uint32_t in_addr_t;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
struct in_addr {
  in_addr_t s_addr;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
struct sockaddr_in {
  sa_family_t sin_family;
  in_port_t sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
struct ipv6_mreq {
  struct in6_addr ipv6mr_multiaddr;
  uint32_t ipv6mr_interface;
};

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
struct ip_mreq {
  struct in_addr imr_multiaddr;
  struct in_addr imr_interface;
};

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/ip.7.html>.
 */
struct ip_mreq_source {
  struct in_addr imr_multiaddr;
  struct in_addr imr_interface;
  struct in_addr imr_sourceaddr;
};

/**
 * Non-POSIX.
 */
struct group_req {
  uint32_t gr_interface;
  struct sockaddr_storage gr_group;
};

/**
 * Non-POSIX.
 */
struct group_source_req {
  uint32_t gsr_interface;
  struct sockaddr_storage gsr_group;
  struct sockaddr_storage gsr_source;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
extern const struct in6_addr in6addr_any;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_in.h.html>.
 */
extern const struct in6_addr in6addr_loopback;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/htonl.html>.
 */
uint32_t htonl(uint32_t hostlong);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/htonl.html>.
 */
uint16_t htons(uint16_t hostshort);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/htonl.html>.
 */
uint32_t ntohl(uint32_t netlong);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/htonl.html>.
 */
uint16_t ntohs(uint16_t netshort);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _NETINET_IN_H */

#include <bits/netinet/in.h>
