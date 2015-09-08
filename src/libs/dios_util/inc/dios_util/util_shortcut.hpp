#ifndef UTIL_SHORTCUT_H
#define UTIL_SHORTCUT_H

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief 快捷操作;
/// 
class DS_UTIL_DECL CShortCut
{
public:

	// 把数值修正到范围内;
	template<class T>
	static T FixInRange(T& v, T min, T max) {

		if(v < min) {
			v = min;
		}
		else if(v > max) {
			v = max;
		}
		return v;
	}

	// 判断数值是否在范围内;
	template<class T>
	static ds_boolean CheckInRange(T v, T min, T max) {

		if(v < min) {
			return false;
		}
		else if(v > max) {
			return false;
		}
		return true;
	}
};

NS_UTIL_END
NS_DS_END

#define DS_SHORTCUT_FIX_IN_RANGE(v, min, max) dios::util::CShortCut::FixInRange(v, min, max)
#define DS_SHORTCUT_CHECK_IN_RANGE(v, min, max) dios::util::CShortCut::CheckInRange(v, min, max)

#endif