#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief 随机数;
/// 
/// 详细说明;
class DS_UTIL_DECL CRandom
{
public:
	CRandom(void);
	~CRandom(void);

	/// \brief 初始化;
	void Init(ds_uint32 seed);

	/// \brief 随机整型;
	ds_int32 RandomInt32(ds_int32 min, ds_int32 max);

	/// \brief 随机浮点数;
	ds_float32 RandomFloat32(ds_float32 min, ds_float32 max);

private:
	ds_uint32 seed_;
};

NS_UTIL_END
NS_DS_END

#endif