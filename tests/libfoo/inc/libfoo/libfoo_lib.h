#ifndef LIBFOO_LIB_H
#define LIBFOO_LIB_H

#include "dios/platform.h"

#ifdef LIBFOO_AS_DLL
	#if  defined ( LIBFOO_EXPORT )
	#define LIBFOO_DECL DS_DLL_EXPORT
	#else
	#define LIBFOO_DECL DS_DLL_IMPORT
	#endif // LIBFOO_EXPORT
#else
	#define LIBFOO_DECL
#endif

#endif // LIBFOO_LIB_H
