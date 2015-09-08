#ifndef DIOS_UTIL_LIB_H
#define DIOS_UTIL_LIB_H

#include "dxm/platform.h"

#ifdef DIOS_UTIL_AS_DLL
	#if  defined ( DIOS_UTIL_EXPORT )
	#define DIOS_UTIL_DECL DIOS_DLL_EXPORT
	#else
	#define DIOS_UTIL_DECL DIOS_DLL_IMPORT
	#endif // DIOS_UTIL_EXPORT
#else
	#define DIOS_UTIL_DECL
#endif

#define NS_UTIL_BEGIN                     namespace util {
#define NS_UTIL_END                       }

#endif // DIOS_UTIL_LIB_H
