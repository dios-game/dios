#ifndef LOG4CPLUS_LIB_H
#define LOG4CPLUS_LIB_H

#include "dios/platform.h"

#ifdef LOG4CPLUS_AS_DLL
	#if  defined ( LOG4CPLUS_EXPORT )
	#define LOG4CPLUS_DECL DS_DLL_EXPORT
	#else
	#define LOG4CPLUS_DECL DS_DLL_IMPORT
	#endif // LOG4CPLUS_EXPORT
#else
	#define LOG4CPLUS_DECL
#endif

#endif // LOG4CPLUS_LIB_H
