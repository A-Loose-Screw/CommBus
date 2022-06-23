#ifndef COMMBUS_HEADERS_H
#define COMMBUS_HEADERS_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  # include <winsock2.h>
  # include <ws2tcpip.h>
  # define SHUT_RDWR 2
  # define close closesocket
  #ifdef _WIN64
    
  #else

  #endif

#elif defined(__APPLE__) || defined(__MACH__)
  #include <TargetConditionals.h>
  #if TARGET_IPHONE_SIMULATOR
    // iOS, tvOS, or watchOS Simulator
  #elif TARGET_OS_MACCATALYST
    // Mac's Catalyst (ports iOS API into Mac, like UIKit).
  #elif TARGET_OS_IPHONE
    
  #elif TARGET_OS_MAC
    
  #else
    #error "Unknown Apple platform"
  #endif
#elif __linux__

#elif __unix__ // all unices not caught above

# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <netdb.h>

#elif defined(_POSIX_VERSION)

#else
  #error "Unknown compiler"
#endif

#if defined(__OpenBSD__) || (defined(__FreeBSD__) && __FreeBSD__ < 5)
# define OS_BSD
# include <netinet/in_systm.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <signal.h>
#include <sys/types.h>

#endif