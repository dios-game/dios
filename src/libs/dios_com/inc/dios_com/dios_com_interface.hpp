#ifndef __DIOS_COM_INTERFACE_H__
#define __DIOS_COM_INTERFACE_H__

#include <map>
#include <string>
#include <typeinfo>
#include <memory>
#include <functional>

#include "dios_util/util_memory.hpp"

namespace dxm{
	typedef	std::string	ComID;
	class ICom:public std::enable_shared_from_this<ICom>
	{
	public:
		typedef std::shared_ptr<ICom> Ptr;
		typedef std::function<ICom* (void)> Factory;
		virtual ~ICom(){}

	public:
		template<class InterfaceType>
		std::shared_ptr<InterfaceType> QueryInterface(){
			return dxm::DynamicCast<InterfaceType>(shared_from_this());
		}
	};
};

#endif // __DIOS_COM_INTERFACE_H__
