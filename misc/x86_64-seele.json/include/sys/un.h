#ifndef _SYS_UN_H
#define _SYS_UN_H

#include <sys/socket.h>

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_un.h.html>.
 */
struct sockaddr_un {
  sa_family_t sun_family;
  char sun_path[108];
};

#endif  /* _SYS_UN_H */
