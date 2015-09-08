#ifndef DIOS_COM_LIB_H
#define DIOS_COM_LIB_H

#include "dxm/platform.h"

#ifdef DIOS_COM_AS_DLL
	#if  defined ( DIOS_COM_EXPORT )
	#define DIOS_COM_DECL DIOS_DLL_EXPORT
	#else
	#define DIOS_COM_DECL DIOS_DLL_IMPORT
	#endif // DIOS_COM_EXPORT
#else
	#define DIOS_COM_DECL
#endif

#endif // DIOS_COM_LIB_H
