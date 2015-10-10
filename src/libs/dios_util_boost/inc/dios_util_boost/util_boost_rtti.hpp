#ifndef DIOS_UTIL_BOOST_RTTI_H
#define DIOS_UTIL_BOOST_RTTI_H

#include <string>
#include <typeinfo>

#include "dios_util_boost_lib.h"
#include "dios_util/util_memory.hpp"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

class DIOS_UTIL_BOOST_DECL IRTTIClass : public std::enable_shared_from_this<IRTTIClass>
{
public:
	typedef std::shared_ptr<IRTTIClass> Ptr;	
	virtual ~IRTTIClass(){}
public:
	template<class InterfaceType>
	std::shared_ptr<InterfaceType> QueryInterface(){
		return dios::DynamicCast<InterfaceType>(shared_from_this());
	}
};

NS_UTIL_BOOST_END
NS_DS_END

#endif //MISC_HELPER_RTTI_H
