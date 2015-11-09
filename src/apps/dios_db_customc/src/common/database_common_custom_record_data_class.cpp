#include "precompiled.h"
#include "database_common_custom_record_data_class.h"

#include "dios_db_table/dios_db_tableinfo.h"

#include "code_file.h"
#include "code_helper.h"

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassBegin( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 表记录\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class RecordData\n");
	file.WriteWithTab("{\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("RecordData(void);\n");
	file.WriteWithTab("RecordData(const RecordData& record_data);\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("~RecordData(void);\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassPublicDirtyFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	记录的修改标记\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline void clear_record_dirty(void) { record_dirty_ = false; memset(col_dirty_, 0, sizeof(col_dirty_)); }\n");
	file.WriteWithTab("inline const bool* col_dirty(void) const { return col_dirty_; }\n");
	file.WriteWithTab("inline bool col_dirty(int index) const { return col_dirty_[index]; }\n");
	file.WriteWithTab("inline bool record_dirty(void) const { return record_dirty_; }\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("inline bool* col_dirty(void) { return col_dirty_; }\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassColFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	获取与设置字段\n");
	file.WriteWithTab(" */\n");
	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		if(table_col_info.type() == dios::kDatabaseColTypeBlob) {
			file.WriteWithTab("void set_%s(const std::string& %s);\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("void set_%s(const void* %s, int size);\n", table_col_info.name().c_str(), table_col_info.name().c_str());
		}
		else {
			file.WriteWithTab("void set_%s(%s %s);\n", 
				table_col_info.name().c_str(), 
				sCodeHelper->GetColTypeCNameReadOnly(table_col_info.type()),
				table_col_info.name().c_str());
		}
		
		file.WriteWithTab("inline %s %s(void) const { return %s_; }\n", 
			sCodeHelper->GetColTypeCNameReadOnly(table_col_info.type()),
			table_col_info.name().c_str(), 
			table_col_info.name().c_str());

		if(i != table_col_count - 1) {
			file.WriteWithTab("\n");
		}
	}
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassParseFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流加载\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void ParseFromArray(const void* buffer, uint size);\n");
	file.WriteWithTab("void ParseFromString(const std::string& buffer);\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassSerializeFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool SerializeToArray(void* buffer, uint& size);\n");
	file.WriteWithTab("bool SerializeToString(std::string* buffer);\n");
	file.WriteWithTab("void SerializeWithCachedSizesToArray(void* buffer, uint size);\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassByteSizeFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出容量\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("uint ByteSize(void);\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassProtectedDirtyFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	设置字段的修改标记\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline void set_col_dirty(uint col_index) { col_dirty_[col_index] = true; record_dirty_ = true; }\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassProtectedMember( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 成员变量\n");
	file.WriteWithTab(" */\n");

	auto table_col_count = table_info.col_info_vector().size();
	for(ds_int32 i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("%s %s_;\n", sCodeHelper->GetColTypeCName(table_col_info.type()), table_col_info.name().c_str());
	}
	file.WriteWithTab("\n");

	file.WriteWithTab("bool col_dirty_[%u];\n", table_col_count);
	file.WriteWithTab("bool record_dirty_;\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteHeaderRecordDataClassBegin(file);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();
	WriteHeaderRecordDataClassStruct(file, table_info);
	WriteHeaderRecordDataClassDestruct(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassPublicDirtyFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassColFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassParseFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassSerializeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassByteSizeFunction(file, table_info);
	file.WriteWithTab("\n");
	file.DecreaseTab();
	file.WriteWithTab("protected:\n");
	file.IncreaseTab();
	WriteHeaderRecordDataClassProtectedDirtyFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordDataClassProtectedMember(file, table_info);
	file.DecreaseTab();
	WriteHeaderRecordDataClassEnd(file);
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	auto table_col_count = table_info.col_info_vector().size();

	file.WriteWithTab("RecordData::RecordData( void ) {\n");
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		const char* init_str = sCodeHelper->GetRecordStructColInitString(table_col_info);
		if(init_str) {
			file.WriteWithTab("	%s\n", init_str);
		}
	}
	file.WriteWithTab("\n");
	file.WriteWithTab("	memset(col_dirty_, 0, sizeof(col_dirty_));\n");
	file.WriteWithTab("	record_dirty_ = false;\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");

	file.WriteWithTab("RecordData::RecordData( const RecordData& record_data ) {\n");
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("	%s_ = record_data.%s();\n", table_col_info.name().c_str(), table_col_info.name().c_str());
	}
	file.WriteWithTab("\n");
	file.WriteWithTab("	record_dirty_ = record_data.record_dirty();\n");
	file.WriteWithTab("	memcpy(col_dirty_, record_data.col_dirty(), sizeof(col_dirty_));\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("RecordData::~RecordData(void) {\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecrodDataClassColFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	获取与设置字段\n");
	file.WriteWithTab(" */\n");
	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		if(table_col_info.type() == dios::kDatabaseColTypeBlob) {
			file.WriteWithTab("void RecordData::set_%s( const std::string& %s ) { \n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("	if(%s == %s_) {\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("		return;\n");
			file.WriteWithTab("	}\n");
			file.WriteWithTab("	%s_ = %s;\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("	set_col_dirty(%d);\n", i);
			file.WriteWithTab("}\n");
			file.WriteWithTab("\n");
			file.WriteWithTab("void RecordData::set_%s( const void* %s, int size ) { \n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("	std::string temp((char*)%s, size);\n", table_col_info.name().c_str());
			file.WriteWithTab("	if(temp == %s_) {\n", table_col_info.name().c_str());
			file.WriteWithTab("		return;\n");
			file.WriteWithTab("	}\n");
			file.WriteWithTab("	%s_ = temp;\n", table_col_info.name().c_str());
			file.WriteWithTab("	set_col_dirty(%d);\n", i);
			file.WriteWithTab("}\n");
		}
		else {
			file.WriteWithTab("void RecordData::set_%s( %s %s ) {\n", 
				table_col_info.name().c_str(), 
				sCodeHelper->GetColTypeCNameReadOnly(table_col_info.type()),
				table_col_info.name().c_str());
			file.WriteWithTab("	if(%s_ == %s) {\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("		return;\n");
			file.WriteWithTab("	}\n");
			file.WriteWithTab("	%s_ = %s;\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			file.WriteWithTab("	set_col_dirty(%d);\n", i);
			file.WriteWithTab("}\n");
		}
		
		if(i != table_col_count - 1) {
			file.WriteWithTab("\n");
		}
	}
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClassParseFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流加载\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void RecordData::ParseFromArray(const void* buffer, uint size) {\n");
	file.WriteWithTab("	xenon::util_boost::CBuffer temp_buffer(buffer, size);\n");
	file.WriteWithTab("	xenon::util_boost::CSerializer serializer(temp_buffer, size, xenon::util::CEndianHelper::ENDIAN_LITTLE);\n");
	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("	%s\n", sCodeHelper->GetColParseString(table_col_info));
	}                                                                    
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("void RecordData::ParseFromString(const std::string& buffer) {\n");
	file.WriteWithTab("	ParseFromArray(buffer.data(), buffer.size());\n");                
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClassSerializeFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool RecordData::SerializeToArray( void* buffer, uint& size ) {\n");
	file.WriteWithTab("	uint rl_size = ByteSize();\n");
	file.WriteWithTab("	if(size < rl_size) {\n");
	file.WriteWithTab("		return false;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	SerializeWithCachedSizesToArray(buffer, rl_size);\n");
	file.WriteWithTab("	size = rl_size;\n");
	file.WriteWithTab("	return true;\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("bool RecordData::SerializeToString( std::string* buffer ) {\n");
	file.WriteWithTab("	uint rl_size = ByteSize();\n");
	file.WriteWithTab("	buffer->resize(rl_size);\n");
	file.WriteWithTab("	SerializeWithCachedSizesToArray(&*buffer->begin(), rl_size);\n");
	file.WriteWithTab("	return true;\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("void RecordData::SerializeWithCachedSizesToArray( void* buffer, uint size ) {\n");
	file.WriteWithTab("	xenon::util_boost::CBuffer temp_buffer(buffer, size);\n");
	file.WriteWithTab("	xenon::util_boost::CSerializer serializer(temp_buffer, xenon::util::CEndianHelper::ENDIAN_LITTLE);\n");

	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("	%s\n", sCodeHelper->GetColSerializeString(table_col_info));
	}
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClassByteSizeFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出容量\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("uint RecordData::ByteSize(void) {\n");
	file.WriteWithTab("	uint size = 0;\n");

	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("	%s\n", sCodeHelper->GetColByteSizeString(table_col_info));
	}
	file.WriteWithTab("	return size;\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteSourceRecordDataClassStruct(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordDataClassDestruct(file);
	file.WriteWithTab("\n");
	WriteSourceRecrodDataClassColFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordDataClassParseFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordDataClassSerializeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordDataClassByteSizeFunction(file, table_info);
}
