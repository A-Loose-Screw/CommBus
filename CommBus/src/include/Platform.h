#ifndef COMMBUS_PLATFORM_DETECTION_H
#define COMMBUS_PLATFORM_DETECTION_H


/**
 * @brief Platform detector
 * 
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #define COMMBUS_PLATFORM_WINDOWS

  #ifdef _WIN64
    #define COMMBUS_PLATFORM_WINDOWS_X86_64
  #else
    #define COMMBUS_PLATFORM_WINDOWS_X86
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #define COMMBUS_PLATFORM_UNIX
  #include <TargetConditionals.h>
  #if TARGET_IPHONE_SIMULATOR
    // iOS, tvOS, or watchOS Simulator
  #elif TARGET_OS_MACCATALYST
    // Mac's Catalyst (ports iOS API into Mac, like UIKit).
  #elif TARGET_OS_IPHONE
    #define COMMBUS_PLATFORM_IOS
  #elif TARGET_OS_MAC
    #define COMMBUS_PLATFORM_MACOS
  #else
    #error "Unknown Apple platform"
  #endif
#elif __linux__
  #define COMMBUS_PLATFORM_LINUX
  #define COMMBUS_PLATFORM_UNIX
#elif __unix__ // all unices not caught above
  #define COMMBUS_PLATFORM_UNIX

#elif defined(_POSIX_VERSION)
  #define COMMBUS_PLATFORM_POSIX

#elif defined(__OpenBSD__) || (defined(__FreeBSD__) && __FreeBSD__ < 5)
  #define OS_BSD
#else
  #error "Unknown compiler"
#endif


#endif


/**
 * @brief Common Headers for CommBus Start
 * & Common defines
 * 
 */
#ifdef COMMBUS_PLATFORM_UNIX
  // Linux and Mac
  #include <sys/socket.h>
  #include <fcntl.h>
  #include <sys/ioctl.h>
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <arpa/inet.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <netdb.h>
  #include <unistd.h>
  #include <tuple>

  #ifndef COMMBUS_ERRNO
  #define COMMBUS_ERRNO errno
  #endif

  #ifndef COMMBUS_WOULDBLOCK
  #define COMMBUS_WOULDBLOCK EWOULDBLOCK
  #endif

#ifdef COMMBUS_PLATFORM_LINUX
// Linux only
#endif

#ifdef COMMBUS_PLATFORM_MACOS
// Mac Only
#endif

#elif defined(COMMBUS_PLATFORM_WINDOWS)
  // Windows only
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <stdio.h>
  #include <stdlib.h>   // Needed for _wtoi

  #pragma comment(lib, "Ws2_32.lib")

  #ifndef COMMBUS_ERRNO
  #define COMMBUS_ERRNO WSAGetLastError()
  #endif

  #ifndef COMMBUS_WOULDBLOCK
  #define COMMBUS_WOULDBLOCK WSAEWOULDBLOCK
  #endif

  #define SHUT_RDWR 2

  #ifndef close
  #define close closesocket
  #endif

#endif
