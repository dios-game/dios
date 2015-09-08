#ifndef __DS_UTIL_BIT_ARRAY_H__ 
#define __DS_UTIL_BIT_ARRAY_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief λ������������; 
/// 
/// ��ϸ˵����Ϊ��ʡ�ڴ�Ķ���������;
class DS_UTIL_DECL CBitArray{
public:
	CBitArray( );
	CBitArray( ds_uint32 size );
	~CBitArray();
	/// \brief ����λ������С;
	void Resize(ds_uint32 size);
	/// \brief ���ö�Ӧ����λ����;
	void Set( ds_uint32 index, ds_boolean val );
	/// \brief ��ȡ��Ӧ����λ����;
	ds_boolean Get( ds_uint32 index );
	/// \brief ������������λ����;
	void Clear();
	/// \brief ��������;string format��size+data;
	void ParseFromString(const std::string& input);
	/// \brief �������ݵ��ַ���;
	bool SerializeToString(std::string* output);

	DS_PROPERTY(ds_uint32, size);
	DS_PROPERTY(ds_uint32, byte_size);
private:
	ds_uint8* data_; ///< �ڴ��ַ;
};

NS_UTIL_END
NS_DS_END

#endif // __DS_UTIL_BIT_ARRAY_H__
