#ifndef TOLUA_LIB_H
#define TOLUA_LIB_H

#include "dios/platform.h"

#ifdef TOLUA_AS_DLL
	#if  defined ( TOLUA_EXPORT )
	#define TOLUA_DECL DS_DLL_EXPORT
	#else
	#define TOLUA_DECL DS_DLL_EXPORT
	#endif // TOLUA_EXPORT
#else
	#define TOLUA_DECL
#endif

#endif // TOLUA_LIB_H
