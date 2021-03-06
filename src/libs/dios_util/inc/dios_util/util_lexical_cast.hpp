#ifndef __DS_UTIL_LEXICAL_CAST_HPP___
#define __DS_UTIL_LEXICAL_CAST_HPP___

#include "dios_util_lib.h"

#include <map>
#include <mutex>

#include <type_traits>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <sstream>

NS_DS_BEGIN
NS_UTIL_BEGIN

namespace detail
{
	const char* const strue = "true";
	const char* const sfalse = "false";

	template <typename T>
	std::string to_string(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	template <typename To, typename From>
	struct Converter
	{
	};
	//to numeric
	template <typename From>
	struct Converter<int, From>
	{
		static int convert(const From& from)
		{
			return std::atoi(from);
		}
	};
	template <typename From>
	struct Converter<unsigned int, From>
	{
		static unsigned int convert(const From& from)
		{
			return static_cast<unsigned int>(std::atoi(from));
		}
	};
	template <typename From>
	struct Converter<long, From>
	{
		static long convert(const From& from)
		{
			return std::atol(from);
		}
	};
// 	template <typename From>
// 	struct Converter<long long, From>
// 	{
// 		static long long convert(const From& from)
// 		{
// 			return std::atoll(from);
// 		}
// 	};
	template <typename From>
	struct Converter<double, From>
	{
		static double convert(const From& from)
		{
			return std::atof(from);
		}
	};
	template <typename From>
	struct Converter<float, From>
	{
		static float convert(const From& from)
		{
			return (float)std::atof(from);
		}
	};
	//to bool
	template <typename From>
	struct Converter<bool, From>
	{
		static typename std::enable_if<std::is_integral<From>::value, bool>::type convert(From from)
		{
			return !!from;
		}
	};
	static bool checkbool(const char* from, const size_t len, const char* s)
	{
		for (size_t i = 0; i < len; i++)
		{
			if (from[i] != s[i])
			{
				return false;
			}
		}
		return true;
	}
	static bool convert(const char* from)
	{
		const unsigned int len = strlen(from);
		if (len != 4 && len != 5)
			throw std::invalid_argument("argument is invalid");
		bool r = true;
		if (len == 4)
		{
			r = checkbool(from, len, strue);
			if (r)
				return true;
		}
		else
		{
			r = checkbool(from, len, sfalse);
			if (r)
				return false;
		}
		throw std::invalid_argument("argument is invalid");
	}
	template <>
	struct Converter<bool, std::string>
	{
		static bool convert(const std::string& from)
		{
			return detail::convert(from.c_str());
		}
	};
	template <>
	struct Converter<bool, const char*>
	{
		static bool convert(const char* from)
		{
			return detail::convert(from);
		}
	};
	template <>
	struct Converter<bool, char*>
	{
		static bool convert(char* from)
		{
			return detail::convert(from);
		}
	};
	template <unsigned N>
	struct Converter<bool, const char[N]>
	{
		static bool convert(const char(&from)[N])
		{
			return detail::convert(from);
		}
	};
	template <unsigned N>
	struct Converter<bool, char[N]>
	{
		static bool convert(const char(&from)[N])
		{
			return detail::convert(from);
		}
	};
	template <>
	struct Converter<std::string, const char*>
	{
		static std::string convert(const char* from)
		{
			return std::string(from);
		}
	};
	template <>
	struct Converter<std::string, char*>
	{
		static std::string convert(char* from)
		{
			return std::string(from);
		}
	};
	template <unsigned N>
	struct Converter<std::string, const char[N]>
	{
		static std::string convert(const char(&from)[N])
		{
			return std::string(from);
		}
	};
	template <unsigned N>
	struct Converter<std::string, char[N]>
	{
		static std::string convert(const char(&from)[N])
		{
			return std::string(from);
		}
	};
	//to string
	template <typename From>
	struct Converter<std::string, From>
	{
		static std::string convert(const From& from)
		{
			return to_string(from);
		}
	};
}
template <typename To, typename From>
typename std::enable_if<!std::is_same<To, From>::value, To>::type lexical_cast(const From& from)
{
	return detail::Converter<To, From>::convert(from);
}
template <typename To, typename From>
typename std::enable_if<std::is_same<To, From>::value, To>::type lexical_cast(const From& from)
{
	return from;
}

NS_UTIL_END
NS_DS_END

#endif // __XENON_EVENT_SET_HPP___