#ifndef COMPONENT_FACTORIES_H
#define COMPONENT_FACTORIES_H

#include "dios_com_interface.hpp"
#include "dios_com_factory.hpp"
#include "dynamic_plugins.h"
#include "pthread/pthread.h"

namespace dios  {

	class CComFactories
	{
	public:
		struct FactoryInfo
		{
			detail::CComFactory::Ptr com_factory;
			CDynamicLib::Ptr denpend_dyn_lib;
		};

		typedef std::shared_ptr<FactoryInfo> FactoryInfoPtr;
		typedef std::map<ComID, FactoryInfoPtr> FactoryMap;

		CComFactories();
		~CComFactories();

		void AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory);  
		void AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory, CDynamicLib::Ptr& dynamic_lib_ptr);

		ICom::Ptr CreateCom(const ComID& com_id);

	private:	   
		pthread_mutex_t mutex_factory_list_;
		FactoryMap com_factory_list_;
	};
}
#endif // COMPONENT_FACTORIES_H
