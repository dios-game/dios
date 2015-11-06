#ifndef __DS_UTIL_STRING_H___
#define __DS_UTIL_STRING_H___

#include "dios_util_lib.h"

#include "util_charset_chs.h"
#include "util_charset_utf8.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	�ַ�������;
 */
class DS_UTIL_DECL CString
{
public:

	// ����ת��;
	template<class SourceCharset, class TargetCharset>
	static std::string ConvertCharset(const std::string& str) {
		return TargetCharset::ws2s(SourceCharset::s2ws(str));
	}

	// �ַ�������;
	template<class Charset>
	static ds_boolean Find(const std::string& str, const std::list<std::string>& word_list) {

		// �ж��ַ��������Ƿ�Ϸ�;
		if(str.length() == 0) {
			return false;
		}

		// ת��Ϊ���ַ�;
		std::wstring w_source_text = Charset::s2ws(str);

		// �����ı�;
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

	// �ַ����滻;
	template<class Charset>
	static std::string Replace(const std::string& str, const std::list<std::string>& word_list, const std::string& replace_word) {

		// �ж��ַ��������Ƿ�Ϸ�;
		if(str.length() == 0) {
			return str;
		}

		// ת��Ϊ���ַ�;
		std::wstring w_source_text = Charset::s2ws(str);
		std::wstring w_replace_word_text = Charset::s2ws(replace_word);

		// �ı��滻;
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

		// ת��ΪASCII;
		return Charset::ws2s(w_source_text);
	}

	// �ַ����ָ�;
	template<class Charset>
	static void Split(const std::string& str, const std::string& separator, std::vector<std::string>& word_array) {

		if(str.length() == 0) {
			return;
		}

		// ת��Ϊ���ַ�;
		std::wstring w_text = Charset::s2ws(str);

		// �и�����;
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