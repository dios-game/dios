#ifndef __DIOS_COM_MACRO_H__
#define __DIOS_COM_MACRO_H__

#include "dios_com_lib.h"
#include <typeinfo>

// ###################################################
/*

PLUGIN_EXPORT(){
	PLUGIN_EXPORT_COM(com_name, class_com)
	PLUGIN_EXPORT_COM(com_name, class_com)
	PLUGIN_EXPORT_COM(com_name, class_com)
}
*/

// ----------------------------------------------
#define REGISTER_COM(class_com)  sComContext->AddFactory<class_com>();
#define REGISTER_COM_WITH_NAME(com_name,class_com)  sComContext->AddFactory<class_com>( com_name );

// ###################################################
#ifdef DIOS_COM_AS_DLL // dynamic plug-in export

#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)
#define _PLUGIN_DLL_DECL _declspec ( dllexport )
#else
#define _PLUGIN_DLL_DECL
#endif // DIOS_PLATFORM_WIN32

#define PLUGIN_EXPORT_BEGIN() \
extern "C" { \
	_PLUGIN_DLL_DECL void  DllPlugin(std::shared_ptr<dios::CDynamicLib>&); \
}; \
extern "C" void  DllPlugin(std::shared_ptr<dios::CDynamicLib>& dyn_lib_ptr) {

#define PLUGIN_EXPORT_COM(com_name,class_com)	 sComContext->AddFactory<class_com>( com_name, dyn_lib_ptr );

#define PLUGIN_EXPORT_END() \
}

#else // static plug-in export

#define _PLUGIN_EXPORT_CLASS_NAME()   PluginExport

#define _PLUGIN_EXPORT_CLASS_INSTANCE_NAME()   PluginExportInstance

#define PLUGIN_EXPORT_BEGIN() \
namespace { \
	class _PLUGIN_EXPORT_CLASS_NAME() \
	{ \
	public: \
	_PLUGIN_EXPORT_CLASS_NAME()(); \
	} _PLUGIN_EXPORT_CLASS_INSTANCE_NAME(); \
	_PLUGIN_EXPORT_CLASS_NAME()::_PLUGIN_EXPORT_CLASS_NAME()() {\ 

#define PLUGIN_EXPORT_COM(com_name,class_com)	 sComContext->AddFactory<class_com>( com_name );

#define PLUGIN_EXPORT_END() \
	} \
}

#endif

#endif //__DIOS_COM_MACRO_H__
