#ifndef LIBMYSQL_LIB_H
#define LIBMYSQL_LIB_H

#include "dios/platform.h"

#ifdef LIBMYSQL_AS_DLL
	#if  defined ( LIBMYSQL_EXPORT )
	#define LIBMYSQL_DECL DS_DLL_EXPORT
	#else
	#define LIBMYSQL_DECL DS_DLL_IMPORT
	#endif // LIBMYSQL_EXPORT
#else
	#define LIBMYSQL_DECL
#endif

#endif // LIBMYSQL_LIB_H
