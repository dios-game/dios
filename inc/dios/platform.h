

#ifndef __DIOS_PLATFORM_H__
#define __DIOS_PLATFORM_H__

#include "platform_config.h"
#include "platform_type.h"
#include "platform_macros.h"

// math.h
#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)

// for math.h on win32 platform
#if !defined(_USE_MATH_DEFINES)
#define _USE_MATH_DEFINES 
#endif // _USE_MATH_DEFINES

#if !defined(isnan)
#define isnan   _isnan
#endif // isnan

#endif // (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)

// std header
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <memory>
#include <functional>

// stdint;
#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)
#if _MSC_VER >= 1600
#include <stdint.h>
#else
#include "./compat/stdint.h"
#endif
#include <WinSock2.h>
#include <Windows.h>
#include <sys/timeb.h>
#else
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#endif

#if (DS_TARGET_PLATFORM == DS_PLATFORM_LINUX)

#define tanf tan
#define sqrtf sqrt
#define cosf cos
#define sinf sin

#endif

#endif  // __DIIOS_PLATFORM_H__