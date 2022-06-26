#ifndef NNG_CONFIG
#define NNG_CONFIG

/**
 * @brief Platform Detection
 * 
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define NNG_PLATFORM_WINDOWS

   #ifdef _WIN64
      #define NNG_PLATFORM_WINDOWS_X86_64
   #else
      #define NNG_PLATFORM_WINDOWS_X86
   #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
      // iOS, tvOS, or watchOS Simulator c++
    #elif TARGET_OS_MACCATALYST
      // Mac's Catalyst (ports iOS API into Mac, like UIKit).
    #elif TARGET_OS_IPHONE
      #define NNG_PLATFORM_IOS
    #elif TARGET_OS_MAC
      #define NNG_PLATFORM_MACOS
      #define NNG_PLATFORM_POSIX
    #else
      #error "Unknown Apple platform"
    #endif
#elif __linux__
  #define NNG_PLATFORM_LINUX
  #define NNG_PLATFORM_UNIX
  #define NNG_PLATFORM_POSIX
#elif __unix__ // all unices not caught above
  #define NNG_PLATFORM_UNIX
  #define NNG_PLATFORM_POSIX

#elif defined(_POSIX_VERSION)
  #define NNG_PLATFORM_POSIX
#else
  #error "Unknown compiler"
#endif



/**
 * @brief Transport configs
 * 
 */
#define NNG_TRANSPORT_INPROC
#define NNG_TRANSPORT_IPC
#define NNG_TRANSPORT_TCP
#define NNG_TRANSPORT_TCS
#define NNG_TRANSPORT_WS
#define NNG_TRANSPORT_WSS

/**
 * @brief Protocols
 * 
 */
#define NNG_PROTO_BUS0
#define NNG_PROTO_PAIR0
#define NNG_PROTO_PAIR1
#define NNG_PROTO_PUSH0
#define NNG_PROTO_PULL0
#define NNG_PROTO_PUB0
#define NNG_PROTO_SUB0
#define NNG_PROTO_REQ0
#define NNG_PROTO_REP0
#define NNG_PROTO_SURVEYOR0
#define NNG_PROTO_RESPONDENT0

#endif