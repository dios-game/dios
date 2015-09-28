#ifndef ZLIB_LIB_H
#define ZLIB_LIB_H

#include "dios/platform.h"

#ifdef ZLIB_AS_DLL
	#if  defined ( ZLIB_EXPORT )
	#define ZLIB_DECL DS_DLL_EXPORT
	#else
	#define ZLIB_DECL DS_DLL_IMPORT
	#endif // ZLIB_EXPORT
#else
	#define ZLIB_DECL
#endif

#endif // ZLIB_LIB_H
