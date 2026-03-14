#ifndef _NETINET_TCP_H
#define _NETINET_TCP_H

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/netinet_tcp.h.html>.
 */
#define TCP_NODELAY 1

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/tcp.7.html>.
 */
#define TCP_MAXSEG 2

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/tcp.7.html>.
 */
#define TCP_KEEPIDLE 4

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/tcp.7.html>.
 */
#define TCP_KEEPINTVL 5

/**
 * Non-POSIX, see <https://www.man7.org/linux/man-pages/man7/tcp.7.html>.
 */
#define TCP_KEEPCNT 6

#endif  /* _NETINET_TCP_H */
