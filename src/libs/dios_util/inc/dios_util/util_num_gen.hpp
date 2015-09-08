#ifndef _DS_UTIL_NUM_GEN_H_
#define _DS_UTIL_NUM_GEN_H_

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief ����������;
/// 
/// ��ϸ˵����ָ��Ϊ����λ�������������ŵ����͡�������[min,max];

template < typename IntType = ds_int32 >
class CNumGen
{
public:
	CNumGen(IntType seed = 0): seed_(seed){}
	~CNumGen(){}

public:
	IntType operator()(IntType min, IntType max)
	{
		IntType tmp = seed_;
		++tmp;
		if (tmp > max || tmp < min)
		{
			tmp = min;
		}
		seed_ = tmp;
		return tmp;
	}

	DS_PROPERTY(IntType, seed);
};

NS_UTIL_END
NS_DS_END

#endif // _DS_UTIL_NUM_GEN_H_
