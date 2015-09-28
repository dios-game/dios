#ifndef BOOST_LIB_H
#define BOOST_LIB_H

#include "dios/platform.h"

#ifdef BOOST_AS_DLL
	#if  defined ( BOOST_EXPORT )
	#define BOOST_DECL DS_DLL_EXPORT
	#else
	#define BOOST_DECL DS_DLL_IMPORT
	#endif // BOOST_EXPORT
#else
	#define BOOST_DECL
#endif

#endif // BOOST_LIB_H
