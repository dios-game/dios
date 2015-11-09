#include "precompiled.h"
#include "dios_db_tableinfo.h"

#include "dios_util/util_crypto.h"

NS_DS_BEGIN

ds_boolean CDatabaseColInfo::operator==( const CDatabaseColInfo& col_info )
{
	if(name_ != col_info.name() || 
		type_ != col_info.type() || 
		char_size_ != col_info.char_size())
	{
		return false;
	}
	return true;
}

ds_boolean CDatabaseColInfo::operator!=( const CDatabaseColInfo& col_info )
{
	return !(*this == col_info);
}

ds_boolean CDatabaseIndexInfo::operator==( const CDatabaseIndexInfo& index_info )
{
	if(name_ != index_info.name() || 
		col_name_array_ != index_info.col_name_array() || 
		is_primary_key_ != index_info.is_primary_key())
	{
		return false;
	}
	return true;
}

ds_boolean CDatabaseIndexInfo::operator!=( const CDatabaseIndexInfo& index_info )
{
	return !(*this == index_info);
}

ds_boolean CDatabaseForeignKeyInfo::operator==( const CDatabaseForeignKeyInfo& foreign_key_info )
{
	if(name_ != foreign_key_info.name() || 
		col_name_ != foreign_key_info.col_name() || 
		foreign_table_name_ != foreign_key_info.foreign_table_name() || 
		foreign_col_name_ != foreign_key_info.foreign_col_name())
	{
		return false;
	}
	return true;
}

ds_boolean CDatabaseForeignKeyInfo::operator!=( const CDatabaseForeignKeyInfo& foreign_key_info )
{
	return !(*this == foreign_key_info);
}

CDatabaseTableInfo::CDatabaseTableInfo( void )
{
}

CDatabaseTableInfo::CDatabaseTableInfo( const std::string& name )
{
	name_ = name;
}

CDatabaseTableInfo::CDatabaseTableInfo( const CDatabaseTableInfo& table_info )
{
	name_ = table_info.name();
	col_info_vector_ = table_info.col_info_vector();
	index_info_vector_ = table_info.index_info_vector();
	foreign_key_info_vector_ = table_info.foreign_key_info_vector();
}

CDatabaseTableInfo::~CDatabaseTableInfo( void )
{

}

void CDatabaseTableInfo::operator=( const CDatabaseTableInfo& table_info )
{
	name_ = table_info.name();
	col_info_vector_ = table_info.col_info_vector();
	index_info_vector_ = table_info.index_info_vector();
	foreign_key_info_vector_ = table_info.foreign_key_info_vector();
}

ds_boolean CDatabaseTableInfo::operator==( const CDatabaseTableInfo& table_info )
{
	// 名称比较;
	if(name_ != table_info.name()) {
		return false;
	}

	// 字段比较;
	if(col_info_vector_.size() != table_info.col_info_vector().size()) {
		return false;
	}
	for(ds_int32 i=0; i<col_info_vector_.size(); ++i) {

		if(col_info_vector_[i] != table_info.col_info_vector()[i]) {
			return false;
		}
	}

	// 索引比较;
	if(index_info_vector_.size() != table_info.index_info_vector().size()) {
		return false;
	}
	for(ds_int32 i=0; i<index_info_vector_.size(); ++i) {

		if(index_info_vector_[i] != table_info.index_info_vector()[i]) {
			return false;
		}
	}

	// 外键比较;
	if(foreign_key_info_vector_.size() != table_info.foreign_key_info_vector().size()) {
		return false;
	}
	for(ds_int32 i=0; i<foreign_key_info_vector_.size(); ++i) {

		if(foreign_key_info_vector_[i] != table_info.foreign_key_info_vector()[i]) {
			return false;
		}
	}
	return true;
}

ds_boolean CDatabaseTableInfo::operator!=( const CDatabaseTableInfo& table )
{
	return !(*this == table);
}

CDatabaseIndexInfo CDatabaseTableInfo::GetPrimaryKey( void )
{
	CDatabaseIndexInfo key;

	ds_uint32 size = index_info_vector_.size();
	for(int i=0; i<size; ++i) {

		if(index_info_vector_[i].is_primary_key()) {
			key = index_info_vector_[i];
		}
	}
	return key;
}

std::string CDatabaseTableInfo::CalcMD5( void ) const
{
	std::string table_text;

	// 表名称;
	table_text.append(name_);

	// 表字段;
	int col_count = col_info_vector_.size();
	for(ds_int32 i=0; i<col_count; ++i) {

		auto col = col_info_vector_[i];
		table_text.append(col.name_);
		table_text.append((char*)&col.type_, sizeof(col.type_));
		table_text.append((char*)&col.char_size_, sizeof(col.char_size_));
	}

	// 表索引;
	int index_info_count = index_info_vector_.size();
	for(ds_int32 i=0; i<index_info_count; ++i)
	{
		auto key = index_info_vector_[i];
		table_text.append(key.name_);
		for(ds_int32 j=0; j<key.col_name_array_.size(); ++j) {
			table_text.append(key.col_name_array_[j]);
		}	
		table_text.append((char*)&key.is_primary_key_, sizeof(key.is_primary_key_));
	}

	// 表外键;
	int foreign_key_count = foreign_key_info_vector_.size();
	for(ds_int32 i=0; i<foreign_key_count; ++i)
	{
		auto extend_key = foreign_key_info_vector_[i];
		table_text.append(extend_key.name_);
		table_text.append(extend_key.col_name_);
		table_text.append(extend_key.foreign_table_name_);
		table_text.append(extend_key.foreign_col_name_);
	}

	// 计算MD5
	return util::CCrypto::Md5(table_text);
}

NS_DS_END