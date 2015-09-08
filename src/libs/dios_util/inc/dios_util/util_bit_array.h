#ifndef __DS_UTIL_BIT_ARRAY_H__ 
#define __DS_UTIL_BIT_ARRAY_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/// \brief 位布尔数组容器; 
/// 
/// 详细说明：为节省内存的而引出的类;
class DS_UTIL_DECL CBitArray{
public:
	CBitArray( );
	CBitArray( ds_uint32 size );
	~CBitArray();
	/// \brief 重置位容器大小;
	void Resize(ds_uint32 size);
	/// \brief 设置对应数据位内容;
	void Set( ds_uint32 index, ds_boolean val );
	/// \brief 获取对应数据位内容;
	ds_boolean Get( ds_uint32 index );
	/// \brief 清理所有数据位内容;
	void Clear();
	/// \brief 加载数据;string format：size+data;
	void ParseFromString(const std::string& input);
	/// \brief 保存数据到字符串;
	bool SerializeToString(std::string* output);

	DS_PROPERTY(ds_uint32, size);
	DS_PROPERTY(ds_uint32, byte_size);
private:
	ds_uint8* data_; ///< 内存地址;
};

NS_UTIL_END
NS_DS_END

#endif // __DS_UTIL_BIT_ARRAY_H__
