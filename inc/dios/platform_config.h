
#ifndef __DIOS_PLATFORM_CONFIG_H__
#define __DIOS_PLATFORM_CONFIG_H__

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which DXM uses.
#define DIOS_PLATFORM_UNKNOWN            0
#define DIOS_PLATFORM_IOS                1
#define DIOS_PLATFORM_ANDROID            2
#define DIOS_PLATFORM_WIN32              3
#define DIOS_PLATFORM_MARMALADE          4
#define DIOS_PLATFORM_LINUX              5
#define DIOS_PLATFORM_BADA               6
#define DIOS_PLATFORM_BLACKBERRY         7
#define DIOS_PLATFORM_MAC                8
#define DIOS_PLATFORM_FREEBSD            9

// Determine target platform by compile environment macro.
#define DIOS_TARGET_PLATFORM             DIOS_PLATFORM_UNKNOWN

// iphone
#if ! DIOS_TARGET_PLATFORM && (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_IOS
#define DIOS_SUPPORT_PVRTC
#endif

// android
#if ! DIOS_TARGET_PLATFORM && defined(ANDROID)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_ANDROID
#endif

// win32
#if ! DIOS_TARGET_PLATFORM && (defined(WIN32) || defined(_WIN64))
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_WIN32
#endif

// linux
#if ! DIOS_TARGET_PLATFORM && defined(__linux__)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_LINUX
#endif

// marmalade
#if ! DIOS_TARGET_PLATFORM && defined(MARMALADE)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_MARMALADE
#endif

// bada
#if ! DIOS_TARGET_PLATFORM && defined(SHP)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_BADA
#endif

// qnx
#if ! DIOS_TARGET_PLATFORM && defined(__QNX__)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM     DIOS_PLATFORM_BLACKBERRY
#endif

// mac
#if ! DIOS_TARGET_PLATFORM && defined(TARGET_OS_MAC)
#undef  DIOS_TARGET_PLATFORM
#define DIOS_TARGET_PLATFORM         DIOS_PLATFORM_MAC
//#define DIOS_SUPPORT_PVRTC
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! DIOS_TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_WIN32)
#pragma warning(disable:4127)  
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4275)
#pragma warning(disable:4344)
#pragma warning(disable:4819)
#endif  // DIOS_PLATFORM_WIN32

#endif  // __DIOS_PLATFORM_CONFIG_H__

