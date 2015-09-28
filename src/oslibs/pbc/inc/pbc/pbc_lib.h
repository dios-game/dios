#ifndef PBC_LIB_H
#define PBC_LIB_H

#include "dios/platform.h"

#ifdef PBC_AS_DLL
	#if  defined ( PBC_EXPORT )
	#define PBC_DECL DS_DLL_EXPORT
	#else
	#define PBC_DECL DS_DLL_IMPORT
	#endif // PBC_EXPORT
#else
	#define PBC_DECL
#endif

#endif // PBC_LIB_H
