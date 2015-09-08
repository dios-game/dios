#ifndef GTEST_LIB_H
#define GTEST_LIB_H

#include "dios/platform.h"

#ifdef GTEST_AS_DLL
	#if  defined ( GTEST_EXPORT )
	#define GTEST_DECL DS_DLL_EXPORT
	#else
	#define GTEST_DECL DS_DLL_IMPORT
	#endif // GTEST_EXPORT
#else
	#define GTEST_DECL
#endif

#endif // GTEST_LIB_H
