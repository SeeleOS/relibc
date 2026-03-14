#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/uio.h>

#define SOCK_STREAM 1

#define SOCK_DGRAM 2

#define SOCK_RAW 3

#define SOCK_NONBLOCK 2048

#define SOCK_CLOEXEC 524288

#define SOCK_RDM 4

#define SOCK_SEQPACKET 5

#define SOL_SOCKET 1

#define SO_DEBUG 1

#define SO_REUSEADDR 2

#define SO_TYPE 3

#define SO_ERROR 4

#define SO_DONTROUTE 5

#define SO_BROADCAST 6

#define SO_SNDBUF 7

#define SO_RCVBUF 8

#define SO_KEEPALIVE 9

#define SO_OOBINLINE 10

#define SO_NO_CHECK 11

#define SO_PRIORITY 12

#define SO_LINGER 13

#define SO_BSDCOMPAT 14

#define SO_REUSEPORT 15

#define SO_PASSCRED 16

#define SO_PEERCRED 17

#define SO_RCVLOWAT 18

#define SO_SNDLOWAT 19

#define SO_RCVTIMEO 20

#define SO_SNDTIMEO 21

#define SO_ACCEPTCONN 30

#define SO_PEERSEC 31

#define SO_SNDBUFFORCE 32

#define SO_RCVBUFFORCE 33

#define SO_PROTOCOL 38

#define SO_DOMAIN 39

#define SOMAXCONN 128

#define MSG_CTRUNC 8

#define MSG_DONTROUTE 4

#define MSG_EOR 128

#define MSG_OOB 1

#define MSG_PEEK 2

#define MSG_TRUNC 32

#define MSG_DONTWAIT 64

#define MSG_WAITALL 256

#define MSG_CMSG_CLOEXEC 1073741824

#define IP_ADD_SOURCE_MEMBERSHIP 70

#define IP_DROP_SOURCE_MEMBERSHIP 71

#define MCAST_JOIN_SOURCE_GROUP 46

#define MCAST_LEAVE_SOURCE_GROUP 47

#define AF_INET 2

#define AF_INET6 10

#define AF_LOCAL AF_UNIX

#define AF_UNIX 1

#define AF_UNSPEC 0

#define PF_INET 2

#define PF_INET6 10

#define PF_LOCAL PF_UNIX

#define PF_UNIX 1

#define PF_UNSPEC 0

#define SHUT_RD 0

#define SHUT_RDWR 2

#define SHUT_WR 1

#define SCM_RIGHTS 1

#define SCM_CREDENTIALS 2

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct linger {
  int l_onoff;
  int l_linger;
};

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct cmsghdr {
  size_t cmsg_len;
  int cmsg_level;
  int cmsg_type;
};

typedef uint32_t socklen_t;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct msghdr {
  void *msg_name;
  socklen_t msg_namelen;
  struct iovec *msg_iov;
  size_t msg_iovlen;
  void *msg_control;
  size_t msg_controllen;
  int msg_flags;
};

typedef uint16_t sa_family_t;

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct sockaddr {
  sa_family_t sa_family;
  char sa_data[14];
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void _cbindgen_export_linger(struct linger linger);

void _cbindgen_export_cmsghdr(struct cmsghdr cmsghdr);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
unsigned char *CMSG_DATA(const struct cmsghdr *cmsg);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct cmsghdr *CMSG_NXTHDR(const struct msghdr *mhdr, const struct cmsghdr *cmsg);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
struct cmsghdr *CMSG_FIRSTHDR(const struct msghdr *mhdr);

size_t CMSG_ALIGN(size_t len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
unsigned int CMSG_SPACE(unsigned int len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_socket.h.html>.
 */
unsigned int CMSG_LEN(unsigned int length);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/accept.html>.
 */
int accept(int socket, struct sockaddr *address, socklen_t *address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/bind.html>.
 */
int bind(int socket, const struct sockaddr *address, socklen_t address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/connect.html>.
 */
int connect(int socket, const struct sockaddr *address, socklen_t address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getpeername.html>.
 */
int getpeername(int socket, struct sockaddr *address, socklen_t *address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getsockname.html>.
 */
int getsockname(int socket, struct sockaddr *address, socklen_t *address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/getsockopt.html>.
 */
int getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/listen.html>.
 */
int listen(int socket, int backlog);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/recv.html>.
 */
ssize_t recv(int socket, void *buffer, size_t length, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/recvfrom.html>.
 */
ssize_t recvfrom(int socket,
                 void *buffer,
                 size_t length,
                 int flags,
                 struct sockaddr *address,
                 socklen_t *address_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/recvmsg.html>.
 */
ssize_t recvmsg(int socket, struct msghdr *msg, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/send.html>.
 */
ssize_t send(int socket, const void *message, size_t length, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sendmsg.html>.
 */
ssize_t sendmsg(int socket, const struct msghdr *msg, int flags);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/sendto.html>.
 */
ssize_t sendto(int socket,
               const void *message,
               size_t length,
               int flags,
               const struct sockaddr *dest_addr,
               socklen_t dest_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/setsockopt.html>.
 */
int setsockopt(int socket,
               int level,
               int option_name,
               const void *option_value,
               socklen_t option_len);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/shutdown.html>.
 */
int shutdown(int socket, int how);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/socket.html>.
 */
int socket(int domain, int kind, int protocol);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/socketpair.html>.
 */
int socketpair(int domain, int kind, int protocol, int *sv);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _SYS_SOCKET_H */

#include <bits/sys/socket.h>
