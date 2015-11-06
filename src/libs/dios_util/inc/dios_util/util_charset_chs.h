#ifndef __DS_UTIL_CHARSET_CHS_H___
#define __DS_UTIL_CHARSET_CHS_H___

#include <string>
#include <list>

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	中文编码;
 */
class DS_UTIL_DECL CCharsetCHS 
{
public:
	
	// 单字节转宽字节;
	static std::wstring s2ws(const std::string& str);

	// 宽字节转单字节;
	static std::string ws2s(const std::wstring& str);
};

NS_UTIL_END
NS_DS_END

#endif