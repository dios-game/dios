#ifndef __DS_UTIL_BIT_TABLE_H__ 
#define __DS_UTIL_BIT_TABLE_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief 位布尔二维数组容器; 
/// 
/// 详细说明：为节省内存的而引出的类;
class DS_UTIL_DECL CBitTable{
public:
	CBitTable();
	CBitTable( ds_uint32 row_size, ds_uint32 column_size  );
	~CBitTable();
	/// \brief 重置位容器大小;
	void Resize( ds_uint32 row_size, ds_uint32 column_size );
	/// \brief 设置对应数据位内容;
	void Set( ds_uint32 row, ds_uint32 column, ds_boolean val );
	/// \brief 获取对应数据位内容;
	ds_boolean Get( ds_uint32 row, ds_uint32 column );
	/// \brief 清理所有数据位内容;
	void Clear();
	/// \brief 加载数据;string format：bit_size+data;
	void ParseFromString(const std::string& input);
	/// \brief 保存数据到字符串;
	bool SerializeToString(std::string* output);

	DS_PROPERTY(ds_uint32, row_size);
	DS_PROPERTY(ds_uint32, column_size);
	DS_PROPERTY(ds_uint32, byte_size);
private:
	ds_uint32 size_; ///< 字节数量;
	ds_uint8* data_; ///< 内存地址;
};

NS_UTIL_END
NS_DS_END

#endif // __DS_UTIL_BIT_TABLE_H__
