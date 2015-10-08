#include "precompiled.h"
#include "dios_com_context.h"
#include "dios_factories.h"
#include "dynamic_plugins.h"
#include "dios_util/util_log.h"

NS_DS_BEGIN
namespace detail{

	CComContext::CComContext() :factories_(new dios::CComFactories), plugins_(new CDynamicPlugins)
	{

	}

	CComContext::~CComContext()
	{
		DS_SAFE_DELETE(factories_);
		DS_SAFE_DELETE(plugins_);
	}

	void CComContext::SetLog(const std::function<void(int, const std::string&)>& log_callback)
	{
		sLog->SetLogCallBack(log_callback);
	}

	void CComContext::LoadPlugin(const std::string & plugin_name)
	{
		if (plugins_)
			plugins_->LoadPlugin(plugin_name);
	}

	void CComContext::AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory)
	{
		if (factories_)
			factories_->AddFactory(com_id, factory);
	}

	void CComContext::AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory, CDynamicLib::Ptr& dynamic_lib_ptr)
	{
		if (factories_)
			factories_->AddFactory(com_id, factory, dynamic_lib_ptr);
	}


	ICom::Ptr CComContext::_CreateCom(const ComID& com_id)
	{
		if (factories_)
			return factories_->CreateCom(com_id);
		return ICom::Ptr();
	}
}

NS_DS_END
