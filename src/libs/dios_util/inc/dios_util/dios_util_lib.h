#ifndef DS_UTIL_LIB_H
#define DS_UTIL_LIB_H

#include "dios/platform.h"

#ifdef DIOS_UTIL_AS_DLL
	#if  defined ( DIOS_UTIL_EXPORT )
	#define DS_UTIL_DECL DS_DLL_EXPORT
	#else
	#define DS_UTIL_DECL DS_DLL_IMPORT
	#endif // DS_UTIL_EXPORT
#else
	#define DS_UTIL_DECL
#endif

#define NS_UTIL_BEGIN                     namespace util {
#define NS_UTIL_END                       }

#endif // DS_UTIL_LIB_H
