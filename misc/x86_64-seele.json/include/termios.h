#ifndef _RELIBC_TERMIOS_H
#define _RELIBC_TERMIOS_H

#include <sys/types.h>
#include <stdint.h>
#include <features.h>

#define TCOOFF 0

#define TCOON 1

#define TCIOFF 2

#define TCION 3

#define TCIFLUSH 0

#define TCOFLUSH 1

#define TCIOFLUSH 2

#define TCSANOW 0

#define TCSADRAIN 1

#define TCSAFLUSH 2

#if defined(__linux__)
#define VINTR 0
#endif

#if defined(__redox__)
#define VINTR 8
#endif

#if defined(__linux__)
#define VQUIT 1
#endif

#if defined(__redox__)
#define VQUIT 9
#endif

#if defined(__linux__)
#define VERASE 2
#endif

#if defined(__redox__)
#define VERASE 3
#endif

#if defined(__linux__)
#define VKILL 3
#endif

#if defined(__redox__)
#define VKILL 5
#endif

#if defined(__linux__)
#define VEOF 4
#endif

#if defined(__redox__)
#define VEOF 0
#endif

#if defined(__linux__)
#define VTIME 5
#endif

#if defined(__redox__)
#define VTIME 17
#endif

#if defined(__linux__)
#define VMIN 6
#endif

#if defined(__redox__)
#define VMIN 16
#endif

#if defined(__linux__)
#define VSWTC 7
#endif

#if defined(__redox__)
#define VSWTC 7
#endif

#if defined(__linux__)
#define VSTART 8
#endif

#if defined(__redox__)
#define VSTART 12
#endif

#if defined(__linux__)
#define VSTOP 9
#endif

#if defined(__redox__)
#define VSTOP 13
#endif

#if defined(__linux__)
#define VSUSP 10
#endif

#if defined(__redox__)
#define VSUSP 10
#endif

#if defined(__linux__)
#define VEOL 11
#endif

#if defined(__redox__)
#define VEOL 1
#endif

#if defined(__linux__)
#define VREPRINT 12
#endif

#if defined(__redox__)
#define VREPRINT 6
#endif

#if defined(__linux__)
#define VDISCARD 13
#endif

#if defined(__redox__)
#define VDISCARD 15
#endif

#if defined(__linux__)
#define VWERASE 14
#endif

#if defined(__redox__)
#define VWERASE 4
#endif

#if defined(__linux__)
#define VLNEXT 15
#endif

#if defined(__redox__)
#define VLNEXT 14
#endif

#if defined(__linux__)
#define VEOL2 16
#endif

#if defined(__redox__)
#define VEOL2 2
#endif

#if defined(__linux__)
#define NCCS 32
#endif

#if defined(__redox__)
#define NCCS 32
#endif

#if defined(__linux__)
#define IGNBRK 1
#endif

#if defined(__redox__)
#define IGNBRK 1
#endif

#if defined(__linux__)
#define BRKINT 2
#endif

#if defined(__redox__)
#define BRKINT 2
#endif

#if defined(__linux__)
#define IGNPAR 4
#endif

#if defined(__redox__)
#define IGNPAR 4
#endif

#if defined(__linux__)
#define PARMRK 8
#endif

#if defined(__redox__)
#define PARMRK 8
#endif

#if defined(__linux__)
#define INPCK 16
#endif

#if defined(__redox__)
#define INPCK 16
#endif

#if defined(__linux__)
#define ISTRIP 32
#endif

#if defined(__redox__)
#define ISTRIP 32
#endif

#if defined(__linux__)
#define INLCR 64
#endif

#if defined(__redox__)
#define INLCR 64
#endif

#if defined(__linux__)
#define IGNCR 128
#endif

#if defined(__redox__)
#define IGNCR 128
#endif

#if defined(__linux__)
#define ICRNL 256
#endif

#if defined(__redox__)
#define ICRNL 256
#endif

#if defined(__linux__)
#define IUCLC 512
#endif

#if defined(__linux__)
#define IXON 1024
#endif

#if defined(__redox__)
#define IXON 512
#endif

#if defined(__linux__)
#define IXANY 2048
#endif

#if defined(__redox__)
#define IXANY 2048
#endif

#if defined(__linux__)
#define IXOFF 4096
#endif

#if defined(__redox__)
#define IXOFF 1024
#endif

#if defined(__linux__)
#define IMAXBEL 8192
#endif

#if defined(__linux__)
#define IUTF8 16384
#endif

#if defined(__linux__)
#define OPOST 1
#endif

#if defined(__redox__)
#define OPOST 1
#endif

#if defined(__linux__)
#define OLCUC 2
#endif

#if defined(__redox__)
#define OLCUC 4
#endif

#if defined(__linux__)
#define ONLCR 4
#endif

#if defined(__redox__)
#define ONLCR 2
#endif

#if defined(__linux__)
#define OCRNL 8
#endif

#if defined(__redox__)
#define OCRNL 8
#endif

#if defined(__linux__)
#define ONOCR 16
#endif

#if defined(__redox__)
#define ONOCR 16
#endif

#if defined(__linux__)
#define ONLRET 32
#endif

#if defined(__redox__)
#define ONLRET 32
#endif

#if defined(__linux__)
#define OFILL 64
#endif

#if defined(__redox__)
#define OFILL 64
#endif

#if defined(__linux__)
#define OFDEL 128
#endif

#if defined(__redox__)
#define OFDEL 128
#endif

#if defined(__linux__)
#define VTDLY 16384
#endif

#if defined(__linux__)
#define VT0 0
#endif

#if defined(__linux__)
#define VT1 16384
#endif

#if defined(__linux__)
#define B0 0
#endif

#if defined(__redox__)
#define B0 0
#endif

#if defined(__linux__)
#define B50 1
#endif

#if defined(__redox__)
#define B50 1
#endif

#if defined(__linux__)
#define B75 2
#endif

#if defined(__redox__)
#define B75 2
#endif

#if defined(__linux__)
#define B110 3
#endif

#if defined(__redox__)
#define B110 3
#endif

#if defined(__linux__)
#define B134 4
#endif

#if defined(__redox__)
#define B134 4
#endif

#if defined(__linux__)
#define B150 5
#endif

#if defined(__redox__)
#define B150 5
#endif

#if defined(__linux__)
#define B200 6
#endif

#if defined(__redox__)
#define B200 6
#endif

#if defined(__linux__)
#define B300 7
#endif

#if defined(__redox__)
#define B300 7
#endif

#if defined(__linux__)
#define B600 8
#endif

#if defined(__redox__)
#define B600 8
#endif

#if defined(__linux__)
#define B1200 9
#endif

#if defined(__redox__)
#define B1200 9
#endif

#if defined(__linux__)
#define B1800 10
#endif

#if defined(__redox__)
#define B1800 10
#endif

#if defined(__linux__)
#define B2400 11
#endif

#if defined(__redox__)
#define B2400 11
#endif

#if defined(__linux__)
#define B4800 12
#endif

#if defined(__redox__)
#define B4800 12
#endif

#if defined(__linux__)
#define B9600 13
#endif

#if defined(__redox__)
#define B9600 13
#endif

#if defined(__linux__)
#define B19200 14
#endif

#if defined(__redox__)
#define B19200 14
#endif

#if defined(__linux__)
#define B38400 15
#endif

#if defined(__redox__)
#define B38400 15
#endif

#if defined(__linux__)
#define B57600 4097
#endif

#if defined(__redox__)
#define B57600 16
#endif

#if defined(__linux__)
#define B115200 4098
#endif

#if defined(__redox__)
#define B115200 17
#endif

#if defined(__linux__)
#define B230400 4099
#endif

#if defined(__redox__)
#define B230400 18
#endif

#if defined(__linux__)
#define B460800 4100
#endif

#if defined(__redox__)
#define B460800 19
#endif

#if defined(__linux__)
#define B500000 4101
#endif

#if defined(__redox__)
#define B500000 20
#endif

#if defined(__linux__)
#define B576000 4102
#endif

#if defined(__redox__)
#define B576000 21
#endif

#if defined(__linux__)
#define B921600 4103
#endif

#if defined(__redox__)
#define B921600 22
#endif

#if defined(__linux__)
#define B1000000 4104
#endif

#if defined(__redox__)
#define B1000000 23
#endif

#if defined(__linux__)
#define B1152000 4105
#endif

#if defined(__redox__)
#define B1152000 24
#endif

#if defined(__linux__)
#define B1500000 4106
#endif

#if defined(__redox__)
#define B1500000 25
#endif

#if defined(__linux__)
#define B2000000 4107
#endif

#if defined(__redox__)
#define B2000000 26
#endif

#if defined(__linux__)
#define B2500000 4108
#endif

#if defined(__redox__)
#define B2500000 27
#endif

#if defined(__linux__)
#define B3000000 4109
#endif

#if defined(__redox__)
#define B3000000 28
#endif

#if defined(__linux__)
#define B3500000 4110
#endif

#if defined(__redox__)
#define B3500000 29
#endif

#if defined(__linux__)
#define B4000000 4111
#endif

#if defined(__redox__)
#define B4000000 30
#endif

#if defined(__linux__)
#define CSIZE 48
#endif

#if defined(__redox__)
#define CSIZE 768
#endif

#if defined(__linux__)
#define CS5 0
#endif

#if defined(__redox__)
#define CS5 0
#endif

#if defined(__linux__)
#define CS6 16
#endif

#if defined(__redox__)
#define CS6 256
#endif

#if defined(__linux__)
#define CS7 32
#endif

#if defined(__redox__)
#define CS7 512
#endif

#if defined(__linux__)
#define CS8 48
#endif

#if defined(__redox__)
#define CS8 768
#endif

#if defined(__linux__)
#define CSTOPB 64
#endif

#if defined(__redox__)
#define CSTOPB 1024
#endif

#if defined(__linux__)
#define CREAD 128
#endif

#if defined(__redox__)
#define CREAD 2048
#endif

#if defined(__linux__)
#define PARENB 256
#endif

#if defined(__redox__)
#define PARENB 4096
#endif

#if defined(__linux__)
#define PARODD 512
#endif

#if defined(__redox__)
#define PARODD 8192
#endif

#if defined(__linux__)
#define HUPCL 1024
#endif

#if defined(__redox__)
#define HUPCL 16384
#endif

#if defined(__linux__)
#define CLOCAL 2048
#endif

#if defined(__redox__)
#define CLOCAL 32768
#endif

#if defined(__linux__)
#define ISIG 1
#endif

#if defined(__redox__)
#define ISIG 128
#endif

#if defined(__linux__)
#define ICANON 2
#endif

#if defined(__redox__)
#define ICANON 256
#endif

#if defined(__linux__)
#define ECHO 8
#endif

#if defined(__redox__)
#define ECHO 8
#endif

#if defined(__linux__)
#define ECHOE 16
#endif

#if defined(__redox__)
#define ECHOE 2
#endif

#if defined(__linux__)
#define ECHOK 32
#endif

#if defined(__redox__)
#define ECHOK 4
#endif

#if defined(__linux__)
#define ECHONL 64
#endif

#if defined(__redox__)
#define ECHONL 16
#endif

#if defined(__linux__)
#define NOFLSH 128
#endif

#if defined(__redox__)
#define NOFLSH 2147483648
#endif

#if defined(__linux__)
#define TOSTOP 256
#endif

#if defined(__redox__)
#define TOSTOP 4194304
#endif

#if defined(__linux__)
#define IEXTEN 32768
#endif

#if defined(__redox__)
#define IEXTEN 1024
#endif

#if defined(__linux__)
/**
 * Sentinel value to disable a control char.
 */
#define _POSIX_VDISABLE 0
#endif

#if defined(__redox__)
/**
 * Sentinel value to disable a control char.
 */
#define _POSIX_VDISABLE 0
#endif

typedef uint32_t tcflag_t;

typedef uint8_t cc_t;

typedef uint32_t speed_t;

#if defined(__linux__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html>.
 */
struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  cc_t c_line;
  cc_t c_cc[NCCS];
  speed_t __c_ispeed;
  speed_t __c_ospeed;
};
#endif

#if defined(__redox__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html>.
 */
struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  cc_t c_cc[NCCS];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetattr.html>.
 */
int tcgetattr(int fd, struct termios *out);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsetattr.html>.
 */
int tcsetattr(int fd, int act, const struct termios *value);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetsid.html>.
 */
pid_t tcgetsid(int fd);

#if defined(__linux__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetispeed.html>.
 */
speed_t cfgetispeed(const struct termios *termios_p);
#endif

#if defined(__redox__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetispeed.html>.
 */
speed_t cfgetispeed(const struct termios *termios_p);
#endif

#if defined(__linux__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetospeed.html>.
 */
speed_t cfgetospeed(const struct termios *termios_p);
#endif

#if defined(__redox__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfgetospeed.html>.
 */
speed_t cfgetospeed(const struct termios *termios_p);
#endif

#if defined(__linux__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetispeed.html>.
 */
int cfsetispeed(struct termios *termios_p, speed_t speed);
#endif

#if defined(__redox__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetispeed.html>.
 */
int cfsetispeed(struct termios *termios_p, speed_t speed);
#endif

#if defined(__linux__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetospeed.html>.
 */
int cfsetospeed(struct termios *termios_p, speed_t speed);
#endif

#if defined(__redox__)
/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/cfsetospeed.html>.
 */
int cfsetospeed(struct termios *termios_p, speed_t speed);
#endif

/**
 * Non-POSIX, 4.4 BSD extension
 *
 * See <https://www.man7.org/linux/man-pages/man3/cfsetispeed.3.html>.
 */
int cfsetspeed(struct termios *termios_p, speed_t speed);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcflush.html>.
 */
int tcflush(int fd, int queue);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcdrain.html>.
 */
int tcdrain(int fd);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsendbreak.html>.
 */
int tcsendbreak(int fd, int _dur);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcgetwinsize.html>.
 */
int tcgetwinsize(int fd, struct winsize *sws);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcsetwinsize.html>.
 */
int tcsetwinsize(int fd, const struct winsize *sws);

/**
 * See <https://pubs.opengroup.org/onlinepubs/9799919799/functions/tcflow.html>.
 */
int tcflow(int fd, int action);

/**
 * Non-POSIX, BSD extension
 *
 * See <https://www.man7.org/linux/man-pages/man3/cfmakeraw.3.html>.
 */
void cfmakeraw(struct termios *termios_p);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* _RELIBC_TERMIOS_H */
