#ifndef LIBCURL_LIB_H
#define LIBCURL_LIB_H

#include "dios/platform.h"

#ifdef LIBCURL_AS_DLL
	#if  defined ( LIBCURL_EXPORT )
	#define LIBCURL_DECL DS_DLL_EXPORT
	#else
	#define LIBCURL_DECL DS_DLL_IMPORT
	#endif // LIBCURL_EXPORT
#else
	#define LIBCURL_DECL
#endif

#endif // LIBCURL_LIB_H
