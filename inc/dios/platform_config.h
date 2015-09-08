
#ifndef __DIOS_PLATFORM_CONFIG_H__
#define __DIOS_PLATFORM_CONFIG_H__

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which DXM uses.
#define DS_PLATFORM_UNKNOWN            0
#define DS_PLATFORM_IOS                1
#define DS_PLATFORM_ANDROID            2
#define DS_PLATFORM_WIN32              3
#define DS_PLATFORM_MARMALADE          4
#define DS_PLATFORM_LINUX              5
#define DS_PLATFORM_BADA               6
#define DS_PLATFORM_BLACKBERRY         7
#define DS_PLATFORM_MAC                8
#define DS_PLATFORM_FREEBSD            9

// Determine target platform by compile environment macro.
#define DS_TARGET_PLATFORM             DS_PLATFORM_UNKNOWN

// iphone
#if ! DS_TARGET_PLATFORM && (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_IOS
#define DS_SUPPORT_PVRTC
#endif

// android
#if ! DS_TARGET_PLATFORM && defined(ANDROID)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_ANDROID
#endif

// win32
#if ! DS_TARGET_PLATFORM && (defined(WIN32) || defined(_WIN64))
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_WIN32
#endif

// linux
#if ! DS_TARGET_PLATFORM && defined(__linux__)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_LINUX
#endif

// marmalade
#if ! DS_TARGET_PLATFORM && defined(MARMALADE)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_MARMALADE
#endif

// bada
#if ! DS_TARGET_PLATFORM && defined(SHP)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_BADA
#endif

// qnx
#if ! DS_TARGET_PLATFORM && defined(__QNX__)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM     DS_PLATFORM_BLACKBERRY
#endif

// mac
#if ! DS_TARGET_PLATFORM && defined(TARGET_OS_MAC)
#undef  DS_TARGET_PLATFORM
#define DS_TARGET_PLATFORM         DS_PLATFORM_MAC
//#define DS_SUPPORT_PVRTC
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! DS_TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)
#pragma warning(disable:4127)  
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4275)
#pragma warning(disable:4344)
#pragma warning(disable:4819)
#endif  // DS_PLATFORM_WIN32

#endif  // __DIOS_PLATFORM_CONFIG_H__

