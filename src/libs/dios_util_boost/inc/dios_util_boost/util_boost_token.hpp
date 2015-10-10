#ifndef ___DIOS_UTIL_BOOST_TOKEN_HPP_____
#define ___DIOS_UTIL_BOOST_TOKEN_HPP_____

#include "dios_util/util_string.h"

#include "dios_util_boost_lib.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

#define DEFAULT_TOKEN_WCHAR L",，"

template < typename string_code>
class TToken{
public:
	typedef std::vector<std::string>::iterator iterator;

	iterator begin() { return strings_.begin(); }
	iterator end() { return strings_.end(); }

	TToken(const std::string& input_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		boost::char_separator<wchar_t> sep(DEFAULT_TOKEN_WCHAR);  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			strings_.push_back(string_code::ws2s(*beg));
		}
	}

	TToken(const std::string& input_string, const std::string& token_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		std::wstring wtoken_string = string_code::s2ws(token_string);
		boost::char_separator<wchar_t> sep(wtoken_string.c_str());  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			strings_.push_back(string_code::ws2s(*beg));
		}
	}

	TToken(const std::string& input_string, const std::wstring& wtoken_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		boost::char_separator<wchar_t> sep(wtoken_string.c_str());  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			strings_.push_back(string_code::ws2s(*beg));
		}
	}

	const std::vector<std::string>& strings(void) { return strings_; }

private:

	std::vector<std::string> strings_;
};

typedef TToken<dios::util::string::uft8> CToken;

template < typename string_code = dios::util::string::uft8>
class TTokenVector:public std::vector<std::string>
{
public:
	TTokenVector(const std::string& input_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		boost::char_separator<wchar_t> sep(DEFAULT_TOKEN_WCHAR);  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			push_back(string_code::ws2s(*beg));
		}
	}

	TTokenVector(const std::string& input_string, const std::string& token_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		std::wstring wtoken_string = string_code::s2ws(token_string);
		boost::char_separator<wchar_t> sep(wtoken_string.c_str());  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			push_back(string_code::ws2s(*beg));
		}
	}

	TTokenVector(const std::string& input_string, const std::wstring& wtoken_string)
	{
		typedef boost::tokenizer<boost::char_separator<wchar_t> ,std::wstring::const_iterator,std::wstring> MyToken;

		boost::char_separator<wchar_t> sep(wtoken_string.c_str());  

		std::wstring winput_string = string_code::s2ws(input_string);
		MyToken tok(winput_string, sep);
		for(MyToken::iterator beg=tok.begin(); beg!=tok.end();++beg){
			push_back(string_code::ws2s(*beg));
		}
	}
};

typedef TTokenVector<dios::util::string::uft8> CTokenVector;

NS_UTIL_BOOST_END
NS_DS_END

#endif