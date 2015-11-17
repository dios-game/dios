#ifndef __DS_UTIL_STRING_H___
#define __DS_UTIL_STRING_H___

#include "dios_util_lib.h"

#include "util_charset_chs.h"
#include "util_charset_utf8.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	字符串助手;
 */
class DS_UTIL_DECL CString
{
public:

	// 编码转换;
	template<class SourceCharset, class TargetCharset>
	static std::string ConvertCharset(const std::string& str) {
		return TargetCharset::ws2s(SourceCharset::s2ws(str));
	}

	// 字符串查找;
	template<class Charset>
	static ds_boolean Find(const std::string& str, const std::list<std::string>& word_list) {

		// 判断字符串长度是否合法;
		if(str.length() == 0) {
			return false;
		}

		// 转换为宽字符;
		std::wstring w_source_text = Charset::s2ws(str);

		// 查找文本;
		ds_boolean is_found = false;
		auto iter = word_list.begin();
		while(iter != word_list.end()) {

			ds_int32 pos = 0;
			std::wstring w_word_text = Charset::s2ws(*iter);

			pos = w_source_text.find(w_word_text, pos);
			if(pos != std::wstring::npos) {
				is_found = true;
				break;
			}
			++iter;
		}
		return is_found;
	}

	// 字符串替换;
	template<class Charset>
	static std::string Replace(const std::string& str, const std::list<std::string>& word_list, const std::string& replace_word) {

		// 判断字符串长度是否合法;
		if(str.length() == 0) {
			return str;
		}

		// 转换为宽字符;
		std::wstring w_source_text = Charset::s2ws(str);
		std::wstring w_replace_word_text = Charset::s2ws(replace_word);

		// 文本替换;
		ds_boolean is_replaced = false;
		auto iter = word_list.begin();
		while(iter != word_list.end()) {

			ds_int32 pos = 0;
			std::wstring w_word_text = Charset::s2ws(*iter);

			while(true) {

				pos = w_source_text.find(w_word_text, pos);
				if(pos == std::wstring::npos) {
					break;
				}
				w_source_text.replace(pos, w_word_text.length(), w_replace_word_text);
				pos += w_replace_word_text.length();
			}
			++iter;
		}

		// 转换为ASCII;
		return Charset::ws2s(w_source_text);
	}

	// 字符串分割;
	template<class Charset>
	static void Split(const std::string& str, const std::string& separator, std::vector<std::string>& word_array) {

		if(str.length() == 0) {
			return;
		}

		// 转换为宽字符;
		std::wstring w_text = Charset::s2ws(str);

		// 切割数组;
		ds_int32 pos = 0;
		std::wstring w_separator_text = Charset::s2ws(separator);

		while(true) {

			ds_int32 fpos = w_text.find(w_separator_text, pos);
			word_array.push_back(Charset::ws2s(w_text.substr(pos, fpos)));

			if(fpos == std::wstring::npos) {
				break;
			}
			pos = fpos + w_separator_text.length();
		}
	}
};

NS_UTIL_END
NS_DS_END

#endif