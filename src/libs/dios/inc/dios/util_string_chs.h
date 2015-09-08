#ifndef __DIOS_UTIL_STRING_CHS_H___
#define __DIOS_UTIL_STRING_CHS_H___

#include <string>
#include <list>

#include "dios_util_lib.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

namespace string 
{
	class DIOS_UTIL_DECL chs 
	{
	public:
		static std::string ws2s(const std::wstring& ws);
		static std::wstring s2ws(const std::string& s);

		static dios_boolean find(const std::string& str, const std::list<std::string>& word_list);
		static std::string replace(const std::string& str, const std::list<std::string>& word_list, const std::string& replace_word);
	};
}

NS_UTIL_END
NS_DIOS_END

#endif