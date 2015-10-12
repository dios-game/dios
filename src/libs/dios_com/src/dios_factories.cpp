#include "precompiled.h"
#include "dios_factories.h"
#include "dios_util/util_log.h"

namespace dios{

	CComFactories::CComFactories()
	{
		sLogInfo("[com:info ] CComponentFactories::CComponentFactories plugins start");

		pthread_mutex_init(&mutex_factory_list_, 0);
	}

	CComFactories::~CComFactories()
	{
		sLogInfo("[com:info ] CComponentFactories::~CComponentFactories plugins stop");

		pthread_mutex_destroy(&mutex_factory_list_);
	}

	void CComFactories::AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory)
	{
		sLogInfo("[com:info ] CComponentRepository::loadPlugin load com(%s)", com_id.c_str());  

		pthread_mutex_lock(&mutex_factory_list_);
		FactoryMap::iterator itor = com_factory_list_.find(com_id);	
		if (itor != com_factory_list_.end()){
			sLogWarn("[com:warn ] CComponentRepository::~loadPlugin com(%s) existed，replace it", com_id.c_str());
			com_factory_list_.erase(itor);
		};

		FactoryInfoPtr temp_factory(new FactoryInfo);
		temp_factory->com_factory = factory;
		com_factory_list_.insert(make_pair(com_id, temp_factory));
		pthread_mutex_unlock(&mutex_factory_list_);

		sLogInfo("[com:warn ] CComponentRepository::loadPlugin com(%s) finished", com_id.c_str());
	}

	void CComFactories::AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory, CDynamicLib::Ptr& dynamic_lib_ptr)
	{
		sLogInfo("[com:info ] CComponentRepository::loadPlugin load com(%s)", com_id.c_str());

		pthread_mutex_lock(&mutex_factory_list_);
		FactoryMap::iterator itor = com_factory_list_.find(com_id);
		if (itor != com_factory_list_.end()){
			sLogWarn("[com:warn ] CComponentRepository::~loadPlugin com(%s) existed，replace it", com_id.c_str());
			com_factory_list_.erase(itor);
		}

		/*
		 *	把插件的引用给工厂一份，只要工厂不释放插件就不会释放;
		 */
		FactoryInfoPtr temp_factory(new FactoryInfo);
		temp_factory->com_factory = factory;
		temp_factory->denpend_dyn_lib = dynamic_lib_ptr;
		com_factory_list_.insert(make_pair(com_id, temp_factory));
		pthread_mutex_unlock(&mutex_factory_list_);

		sLogInfo("[com:warn ] CComponentRepository::loadPlugin com(%s) finished", com_id.c_str());
	}

	ICom::Ptr CComFactories::CreateCom(const ComID& com_id)
	{
		pthread_mutex_lock(&mutex_factory_list_);
		FactoryMap::iterator itor = com_factory_list_.find(com_id);
		if (itor == com_factory_list_.end())
		{
			sLogError("[com:error] CComponentRepository::createPlugin create com (%s) failed [ com doesnt existed ]", com_id.c_str());
			pthread_mutex_unlock(&mutex_factory_list_);
			return ICom::Ptr();
		}
		/*
		 *	此处创建的时候会把工厂的引用给组件一份，组件不释放工厂就不会释放，工厂是不释放插件就不会释放。
		 */
		ICom::Ptr com_ptr = itor->second->com_factory->CreateCom();
		pthread_mutex_unlock(&mutex_factory_list_);
		return com_ptr;
	} 
}



