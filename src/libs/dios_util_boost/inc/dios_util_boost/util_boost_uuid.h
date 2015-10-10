#ifndef ___DIOS_UTIL_BOOST_UUID_HPP___
#define ___DIOS_UTIL_BOOST_UUID_HPP___

#include "dios_util_boost_lib.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 *	UUID����������;
 */
class DIOS_UTIL_BOOST_DECL CUuid
{
public:

	// ΨһUUID;
	static boost::uuids::uuid CreateUuid(void);

	// �ַ���ת��UUID;
	static boost::uuids::uuid CreateUuid(const std::string& str);

	// ��UUID;
	static boost::uuids::uuid CreateNilUuid(void);
};

NS_UTIL_BOOST_END
NS_DS_END

#endif
