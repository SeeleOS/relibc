#ifndef _RELIBC_IFADDRS_H
#define _RELIBC_IFADDRS_H

#include <features.h>
#include <netinet/in.h>
#include <sys/socket.h>

union ifaddrs_ifa_ifu {
  struct sockaddr *ifu_broadaddr;
  struct sockaddr *ifu_dstaddr;
};

struct ifaddrs {
  struct ifaddrs *ifa_next;
  char *ifa_name;
  unsigned int ifa_flags;
  struct sockaddr *ifa_addr;
  struct sockaddr *ifa_netmask;
  union ifaddrs_ifa_ifu ifa_ifu;
  void *ifa_data;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void freeifaddrs(struct ifaddrs *ifa);

int getifaddrs(struct ifaddrs **ifap);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_IFADDRS_H */

#define ifa_broadaddr ifa_ifu.ifu_broadaddr
#define ifa_dstaddr ifa_ifu.ifu_dstaddr
