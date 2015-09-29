#ifndef CRASH_HANDLER_LIB_H
#define CRASH_HANDLER_LIB_H

#include "dios/platform.h"

#ifdef CRASH_HANDLER_AS_DLL
	#if  defined ( CRASH_HANDLER_EXPORT )
	#define CRASH_HANDLER_DECL DS_DLL_EXPORT
	#else
	#define CRASH_HANDLER_DECL DS_DLL_IMPORT
	#endif // CRASH_HANDLER_EXPORT
#else
	#define CRASH_HANDLER_DECL
#endif

#endif // CRASH_HANDLER_LIB_H
