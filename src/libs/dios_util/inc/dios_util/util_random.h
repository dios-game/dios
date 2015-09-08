#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief �����;
/// 
/// ��ϸ˵��;
class DS_UTIL_DECL CRandom
{
public:
	CRandom(void);
	~CRandom(void);

	/// \brief ��ʼ��;
	void Init(ds_uint32 seed);

	/// \brief �������;
	ds_int32 RandomInt32(ds_int32 min, ds_int32 max);

	/// \brief ���������;
	ds_float32 RandomFloat32(ds_float32 min, ds_float32 max);

private:
	ds_uint32 seed_;
};

NS_UTIL_END
NS_DS_END

#endif