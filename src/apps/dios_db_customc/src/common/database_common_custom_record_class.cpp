#include "precompiled.h"
#include "database_common_custom_record_class.h"

#include "dios_db_table/dios_db_tableinfo.h"

#include "code_file.h"
#include "code_helper.h"

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassBegin( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 表记录\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class RecordImpl : public Record\n");
	file.WriteWithTab("{\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassStruct( CCodeFile& file )
{
	file.WriteWithTab("typedef boost::shared_ptr<RecordImpl> Ptr;\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("RecordImpl(void);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("~RecordImpl(void);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassColFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	获取与设置字段\n");
	file.WriteWithTab(" */\n");
	
	auto table_col_count = table_info.col_info_vector().size();
	for(int i=0; i<table_col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		if(table_col_info.type() == dios::kDatabaseColTypeBlob) {
			file.WriteWithTab("inline void set_%s(const void* %s, int size) { record_data_.set_%s(%s, size); }\n", 
				table_col_info.name().c_str(), 
				table_col_info.name().c_str(), 
				table_col_info.name().c_str(),
				table_col_info.name().c_str());
		}
		else {
			file.WriteWithTab("inline void set_%s(%s %s) { record_data_.set_%s(%s); }\n", 
				table_col_info.name().c_str(), 
				sCodeHelper->GetColTypeCNameReadOnly(table_col_info.type()),
				table_col_info.name().c_str(), 
				table_col_info.name().c_str(),
				table_col_info.name().c_str());
		}

		file.WriteWithTab("inline %s %s(void) { return record_data_.%s(); }\n", 
			sCodeHelper->GetColTypeCNameReadOnly(table_col_info.type()),
			table_col_info.name().c_str(), 
			table_col_info.name().c_str());

		if(i != table_col_count - 1) {
			file.WriteWithTab("\n");
		}
	}
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassParseFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流加载\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void ParseFromArray(const void* buffer, uint size);\n");
	file.WriteWithTab("void ParseFromString(const std::string& buffer);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassSerializeFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool SerializeToArray(void* buffer, uint& size);\n");
	file.WriteWithTab("bool SerializeToString(std::string* buffer);\n");
	file.WriteWithTab("void SerializeWithCachedSizesToArray(void* buffer, uint size);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassByteSizeFunction( CCodeFile& file, dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出容量\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("uint ByteSize(void);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassIsCommitNecessaryFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	提交是否必要（被删除的/被设脏的记录需要提交）\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline bool IsCommitNecessary(void) { return (commit_object_ && (commit_object_->is_deleted() || record_data_.record_dirty())); }\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassCommitFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void Commit(boost::function<void(bool)> func);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassSetDeletedFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	删除标记函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void set_deleted(void);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassInitCommitObjectFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	设置定向函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void InitCommitObject(DatabaseCustomType dest_type, const char* dest_id, CommitStatus status);\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassRecordDataFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	返回记录数据\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline RecordData& record_data(void) { return record_data_; }\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassCommitObjectFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	返回提交对象\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline CommitObject* commit_object(void) { return commit_object_; }\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassProtectedMember( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 成员变量\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("RecordData record_data_;\n");
	file.WriteWithTab("DatabaseCustomType dest_type_;\n");
	file.WriteWithTab("std::string dest_id_;\n");
	file.WriteWithTab("CommitObject* commit_object_;\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseCommonCustomRecordClass::WriteHeaderRecordClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteHeaderRecordClassBegin(file);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();
	WriteHeaderRecordClassStruct(file);
	WriteHeaderRecordClassDestruct(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassColFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassParseFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassSerializeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassByteSizeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassIsCommitNecessaryFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassCommitFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassSetDeletedFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassInitCommitObjectFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassRecordDataFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderRecordClassCommitObjectFunction(file);
	file.DecreaseTab();
	file.WriteWithTab("protected:\n");
	file.IncreaseTab();
	WriteHeaderRecordClassProtectedMember(file);
	file.DecreaseTab();
	WriteHeaderRecordClassEnd(file);
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteSourceRecordClassStruct(file);
	file.WriteWithTab("\n");
	WriteSourceRecordClassDestruct(file);
	file.WriteWithTab("\n");
	WriteSourceRecordClassParseFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordClassSerializeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordClassByteSizeFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordClassCommitFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceRecordClassSetDeletedFunction(file);
	file.WriteWithTab("\n");
	WriteSourceRecordClassInitCommitObjectFunction(file);
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassInitCommitObjectFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 设置目标\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void RecordImpl::InitCommitObject( DatabaseCustomType dest_type, const char* dest_id, CommitStatus status ) {\n");
	file.WriteWithTab("	// 已经存在提交对象\n");
	file.WriteWithTab("	XE_ASSERT(!commit_object_, \"commit_object_ already existed!\");\n");
	file.WriteWithTab("	switch(dest_type)\n");
	file.WriteWithTab("	{\n");
	file.WriteWithTab("	case kDatabaseSqlCustom: { commit_object_ = new DatabaseSqlCommitObject(dest_id, status, &record_data_); } break;\n");
	file.WriteWithTab("	case kDatabaseCacheCustom: { commit_object_ = new DatabaseCacheCommitObject(dest_id, status, &record_data_); } break;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	\n");
	file.WriteWithTab("	dest_type_ = dest_type;\n");
	file.WriteWithTab("	dest_id_ = dest_id;\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassStruct( CCodeFile& file )
{
	file.WriteWithTab("RecordImpl::RecordImpl( void ) {\n");
	file.WriteWithTab("	commit_object_ = 0;\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("RecordImpl::~RecordImpl( void ) {\n");
	file.WriteWithTab("	XE_SAFE_DELETE(commit_object_);\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassParseFunction( CCodeFile& file, const dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流加载\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void RecordImpl::ParseFromArray( const void* buffer, uint size ) {\n");
	file.WriteWithTab("	xenon::util_boost::CBuffer temp_buffer(buffer, size);\n");
	file.WriteWithTab("	xenon::util_boost::CSerializer serializer(temp_buffer, size, xenon::util::CEndianHelper::ENDIAN_LITTLE);\n");
	file.WriteWithTab("	DatabaseCustomType dest_type;\n");
	file.WriteWithTab("	std::string dest_id;\n");
	file.WriteWithTab("	CommitStatus commit_status;\n");
	file.WriteWithTab("	\n");
	file.WriteWithTab("	serializer>>dest_type;\n");
	file.WriteWithTab("	serializer>>dest_id;\n");
	file.WriteWithTab("	serializer>>commit_status;\n");
	file.WriteWithTab("	serializer.Read(record_data_.col_dirty(), sizeof(bool)*Info::GetInstancePtr()->GetColCount());\n");
	file.WriteWithTab("	record_data_.ParseFromArray((char*)buffer+serializer.seeker(), size-serializer.seeker());\n");
	file.WriteWithTab("	\n");
	file.WriteWithTab("	InitCommitObject(dest_type, dest_id.c_str(), commit_status);\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("void RecordImpl::ParseFromString( const std::string& buffer ) {\n");
	file.WriteWithTab("	ParseFromArray(buffer.data(), buffer.size());\n");                
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassSerializeFunction( CCodeFile& file, const dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool RecordImpl::SerializeToArray( void* buffer, uint& size ) {\n");
	file.WriteWithTab("	uint rl_size = ByteSize();\n");
	file.WriteWithTab("	if(size < rl_size) {\n");
	file.WriteWithTab("		return false;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	SerializeWithCachedSizesToArray(buffer, rl_size);\n");
	file.WriteWithTab("	size = rl_size;\n");
	file.WriteWithTab("	return true;\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("bool RecordImpl::SerializeToString( std::string* buffer ) {\n");
	file.WriteWithTab("	uint rl_size = ByteSize();\n");
	file.WriteWithTab("	buffer->resize(rl_size);\n");
	file.WriteWithTab("	SerializeWithCachedSizesToArray(&*buffer->begin(), rl_size);\n");
	file.WriteWithTab("	return true;\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("void RecordImpl::SerializeWithCachedSizesToArray( void * buffer, uint size ) {\n");
	file.WriteWithTab("	xenon::util_boost::CBuffer temp_buffer(buffer, size);\n");
	file.WriteWithTab("	xenon::util_boost::CSerializer serializer(temp_buffer, xenon::util::CEndianHelper::ENDIAN_LITTLE);\n");
	file.WriteWithTab("	CommitStatus commit_status = (commit_object_) ? commit_object_->commit_status() : kCommitStatusNone;\n");
	file.WriteWithTab("	serializer<<dest_type_;\n");
	file.WriteWithTab("	serializer<<dest_id_;\n");
	file.WriteWithTab("	serializer<<commit_status;\n");
	file.WriteWithTab("	serializer.Write(record_data_.col_dirty(), sizeof(bool)*Info::GetInstancePtr()->GetColCount());\n");
	file.WriteWithTab("	uint record_data_size = size - serializer.size();\n");
	file.WriteWithTab("	record_data_.SerializeWithCachedSizesToArray((char*)buffer+serializer.size(), record_data_size);\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassByteSizeFunction( CCodeFile& file, const dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	二进制流导出容量\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("uint RecordImpl::ByteSize( void ) {\n");
	file.WriteWithTab("	uint rl_size = 0;\n");
	file.WriteWithTab("	rl_size += sizeof(dest_type_);\n");
	file.WriteWithTab("	rl_size += sizeof(unsigned short) + dest_id_.size();\n");
	file.WriteWithTab("	rl_size += sizeof(CommitStatus);\n");
	file.WriteWithTab("	rl_size += sizeof(bool)*Info::GetInstancePtr()->GetColCount();\n");
	file.WriteWithTab("	rl_size += record_data_.ByteSize();\n");
	file.WriteWithTab("	return rl_size;\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassCommitFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void RecordImpl::Commit( boost::function<void(bool)> func ) {\n");
	file.WriteWithTab("	if(!commit_object_) {\n");
	file.WriteWithTab("		return;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	commit_object_->Commit(func);\n");
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomRecordClass::WriteSourceRecordClassSetDeletedFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	删除标记函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void RecordImpl::set_deleted( void ) {\n");
	file.WriteWithTab("	if(!commit_object_) {\n");
	file.WriteWithTab("		return;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	commit_object_->set_deleted();\n");
	file.WriteWithTab("}\n");
}
