#ifndef ___DIOS_UTIL_BOOST_UUID_HPP___
#define ___DIOS_UTIL_BOOST_UUID_HPP___

#include "dios_util_boost_lib.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 *	UUID简易生成类;
 */
class DIOS_UTIL_BOOST_DECL CUuid
{
public:

	// 唯一UUID;
	static boost::uuids::uuid CreateUuid(void);

	// 字符串转换UUID;
	static boost::uuids::uuid CreateUuid(const std::string& str);

	// 空UUID;
	static boost::uuids::uuid CreateNilUuid(void);
};

NS_UTIL_BOOST_END
NS_DS_END

#endif
