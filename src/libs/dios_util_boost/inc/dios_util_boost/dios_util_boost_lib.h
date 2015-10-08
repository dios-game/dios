#ifndef DIOS_UTIL_BOOST_LIB_H
#define DIOS_UTIL_BOOST_LIB_H

#include "dios/platform.h"

#ifdef DIOS_UTIL_BOOST_AS_DLL
	#if  defined ( DIOS_UTIL_BOOST_EXPORT )
	#define DIOS_UTIL_BOOST_DECL DS_DLL_EXPORT
	#else
	#define DIOS_UTIL_BOOST_DECL DS_DLL_IMPORT
	#endif // DIOS_UTIL_BOOST_EXPORT
#else
	#define DIOS_UTIL_BOOST_DECL
#endif

#endif // DIOS_UTIL_BOOST_LIB_H
