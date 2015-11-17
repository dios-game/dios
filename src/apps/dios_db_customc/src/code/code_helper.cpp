#include "precompiled.h"
#include "code_helper.h"

/*
 *	枚举对应代码中的类型;
 */
static char* c_col_type_name[dios::kDatabaseColTypeMax] = {
	"",
	"int16",
	"uint16",
	"int32",
	"uint32",
	"int64",
	"float",
	"std::string",
	"std::string",
	"uuid",
	"char", 
};

static char* c_col_type_name_read_only[dios::kDatabaseColTypeMax] = {
	"",
	"int16",
	"uint16",
	"int32",
	"uint32",
	"int64",
	"float",
	"const std::string&",
	"const std::string&",
	"const uuid&",
	"char", 
};

static char* enum_col_type_name[dios::kDatabaseColTypeMax] = {
	"dios::kDatabaseColTypeNil",
	"dios::kDatabaseColTypeSmallInt",
	"dios::kDatabaseColTypeUnsignedSmallInt",
	"dios::kDatabaseColTypeInt",
	"dios::kDatabaseColTypeUnsignedInt",
	"dios::kDatabaseColTypeInt64",
	"dios::kDatabaseColTypeFloat",
	"dios::kDatabaseColTypeString",
	"dios::kDatabaseColTypeBlob",
	"dios::kDatabaseColTypeUuid",
	"dios::kDatabaseColTypeChar", 
};

const char* CCodeHelper::GetColTypeCName( dios::DatabaseColType col_type )
{
	return c_col_type_name[col_type];
}

const char* CCodeHelper::GetColTypeCNameReadOnly( dios::DatabaseColType col_type )
{
	return c_col_type_name_read_only[col_type];
}

const char* CCodeHelper::GetColTypeEnumName( dios::DatabaseColType col_type )
{
	return enum_col_type_name[col_type];
}

const char* CCodeHelper::GetRecordStructColInitString( const dios::CDatabaseColInfo& col_info )
{
	static char col_init_string[128];

	switch(col_info.type())
	{
	case dios::kDatabaseColTypeSmallInt:
	case dios::kDatabaseColTypeUnsignedSmallInt:
	case dios::kDatabaseColTypeInt:
	case dios::kDatabaseColTypeUnsignedInt:
	case dios::kDatabaseColTypeInt64:
	case dios::kDatabaseColTypeChar:
		{
			sprintf(col_init_string, "%s_ = 0;", col_info.name().c_str());
		}
		break;
	case dios::kDatabaseColTypeFloat:
		{
			sprintf(col_init_string, "%s_ = 0.0f;", col_info.name().c_str());
		}
		break;
	case dios::kDatabaseColTypeString:
	case dios::kDatabaseColTypeBlob:
		{
			return 0;
		}
		break;
	case dios::kDatabaseColTypeUuid:
		{
			sprintf(col_init_string, "%s_ = dios::util_boost::CUuid::CreateNilUuid();", col_info.name().c_str());
		}
		break;
	}
	return col_init_string;
}

const char* CCodeHelper::GetColByteSizeString( const dios::CDatabaseColInfo& col_info )
{
	static char col_byte_size_string[4096];

	switch(col_info.type())
	{
	case dios::kDatabaseColTypeSmallInt: 
	case dios::kDatabaseColTypeUnsignedSmallInt:
	case dios::kDatabaseColTypeInt:
	case dios::kDatabaseColTypeUnsignedInt:
	case dios::kDatabaseColTypeInt64:
	case dios::kDatabaseColTypeFloat:
	case dios::kDatabaseColTypeUuid:
	case dios::kDatabaseColTypeChar:
		{
			sprintf(col_byte_size_string, "size += sizeof(%s_);", col_info.name().c_str());
		}
		break;
	case dios::kDatabaseColTypeString:
		{
			sprintf(col_byte_size_string, "size += %s_.length()+sizeof(uint16);", col_info.name().c_str());
		}
		break;
	case dios::kDatabaseColTypeBlob:
		{
			sprintf(col_byte_size_string, "size += %s_.size()+sizeof(uint16);", col_info.name().c_str());
		}
		break;
	}
	return col_byte_size_string;
}

const char* CCodeHelper::GetColSerializeString( const dios::CDatabaseColInfo& col_info )
{
	static char col_serialize_string[4096];

	switch(col_info.type())
	{
	case dios::kDatabaseColTypeSmallInt: 
	case dios::kDatabaseColTypeUnsignedSmallInt:
	case dios::kDatabaseColTypeInt:
	case dios::kDatabaseColTypeUnsignedInt:
	case dios::kDatabaseColTypeInt64:
	case dios::kDatabaseColTypeFloat:
	case dios::kDatabaseColTypeString:
	case dios::kDatabaseColTypeBlob:
	case dios::kDatabaseColTypeUuid:
	case dios::kDatabaseColTypeChar:
		{
			sprintf(col_serialize_string, "serializer<<%s_;", col_info.name().c_str());
		}
		break;
	}
	return col_serialize_string;
}

const char* CCodeHelper::GetColParseString( const dios::CDatabaseColInfo& col_info )
{
	static char col_parse_string[4096];

	switch(col_info.type())
	{
	case dios::kDatabaseColTypeSmallInt: 
	case dios::kDatabaseColTypeUnsignedSmallInt:
	case dios::kDatabaseColTypeInt:
	case dios::kDatabaseColTypeUnsignedInt:
	case dios::kDatabaseColTypeInt64:
	case dios::kDatabaseColTypeFloat:
	case dios::kDatabaseColTypeString:
	case dios::kDatabaseColTypeBlob:
	case dios::kDatabaseColTypeUuid:
	case dios::kDatabaseColTypeChar:
		{
			sprintf(col_parse_string, "serializer>>%s_;", col_info.name().c_str());
		}
		break;
	}
	return col_parse_string;
}
