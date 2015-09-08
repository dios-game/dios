#ifndef __DS_UTIL_BIT_TABLE_H__ 
#define __DS_UTIL_BIT_TABLE_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief λ������ά��������; 
/// 
/// ��ϸ˵����Ϊ��ʡ�ڴ�Ķ���������;
class DS_UTIL_DECL CBitTable{
public:
	CBitTable();
	CBitTable( ds_uint32 row_size, ds_uint32 column_size  );
	~CBitTable();
	/// \brief ����λ������С;
	void Resize( ds_uint32 row_size, ds_uint32 column_size );
	/// \brief ���ö�Ӧ����λ����;
	void Set( ds_uint32 row, ds_uint32 column, ds_boolean val );
	/// \brief ��ȡ��Ӧ����λ����;
	ds_boolean Get( ds_uint32 row, ds_uint32 column );
	/// \brief ������������λ����;
	void Clear();
	/// \brief ��������;string format��bit_size+data;
	void ParseFromString(const std::string& input);
	/// \brief �������ݵ��ַ���;
	bool SerializeToString(std::string* output);

	DS_PROPERTY(ds_uint32, row_size);
	DS_PROPERTY(ds_uint32, column_size);
	DS_PROPERTY(ds_uint32, byte_size);
private:
	ds_uint32 size_; ///< �ֽ�����;
	ds_uint8* data_; ///< �ڴ��ַ;
};

NS_UTIL_END
NS_DS_END

#endif // __DS_UTIL_BIT_TABLE_H__
