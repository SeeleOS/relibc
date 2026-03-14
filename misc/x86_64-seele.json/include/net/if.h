#ifndef _NET_IF_H
#define _NET_IF_H

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/net_if.h.html>.
 */
#define IF_NAMESIZE 16

#define IFF_UP 1

#define IFF_BROADCAST 2

#define IFF_DEBUG 4

#define IFF_LOOPBACK 8

#define IFF_POINTOPOINT 16

#define IFF_NOTRAILERS 32

#define IFF_RUNNING 64

#define IFF_NOARP 128

#define IFF_PROMISC 256

#define IFF_ALLMULTI 512

#define IFF_MASTER 1024

#define IFF_SLAVE 2048

#define IFF_MULTICAST 4096

#define IFF_PORTSEL 8192

#define IFF_AUTOMEDIA 16384

#define IFF_DYNAMIC 32768

#define IFF_LOWER_UP 65536

#define IFF_DORMANT 131072

#define IFF_ECHO 262144

#define IFF_VOLATILE ((((((((IFF_LOOPBACK | IFF_POINTOPOINT) | IFF_BROADCAST) | IFF_ECHO) | IFF_MASTER) | IFF_SLAVE) | IFF_RUNNING) | IFF_LOWER_UP) | IFF_DORMANT)

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/net_if.h.html>.
 */
struct if_nameindex {
  unsigned int if_index;
  const char *if_name;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/if_freenameindex.html>.
 *
 * # Safety
 * this is a no-op: the list returned by if_nameindex() is a ref to a constant
 */
void if_freenameindex(struct if_nameindex *s);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/if_indextoname.html>.
 *
 * # Safety
 * Returns only static lifetime references to const names, does not reuse the buf pointer.
 * Returns NULL in case of not found + ERRNO being set to ENXIO.
 * Currently only checks against inteface index 1.
 */
const char *if_indextoname(unsigned int idx, char *buf);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/if_nameindex.html>.
 *
 * # Safety
 * Returns a constant pointer to a pre defined const stub list
 * The end of the list is determined by an if_nameindex struct having if_index 0 and if_name NULL
 */
const struct if_nameindex *if_nameindex(void);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/if_nametoindex.html>.
 *
 * # Safety
 * Compares the name to a constant string and only returns an int as a result.
 * An invalid name string will return an index of 0
 */
unsigned int if_nametoindex(const char *name);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _NET_IF_H */
