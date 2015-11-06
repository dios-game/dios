#include "precompiled.h"
#include "dios_db_tableinfo_loader.h"

#include "dios_util/util_log.h"
#include "rapidxml/rapidxml_utils.hpp"

#include "dios_util/util_rapidxml.h"
#include "dios_util/util_string.h"

NS_DS_BEGIN

static char* kColTypeName[DATABASE_COL_TYPE_MAX] = {
	"null",
	"int16",
	"uint16",
	"int32",
	"uint32",
	"int64",
	"float",
	"string",
	"bytes",
	"uuid",
	"char",
};

CDatabaseTableInfoLoader::CDatabaseTableInfoLoader( void )
{

}

CDatabaseTableInfoLoader::~CDatabaseTableInfoLoader( void )
{

}

DatabaseColType CDatabaseTableInfoLoader::ColTypeName2Type( const std::string& name )
{
	for(ds_int32 i=0; i<DATABASE_COL_TYPE_MAX; ++i) {

		if(name == kColTypeName[i]) {
			return static_cast<DatabaseColType>(i);
		}
	}
	return DATABASE_COL_TYPE_NULL;
}

std::shared_ptr<CDatabaseTableInfo> CDatabaseTableInfoLoader::LoadTableFromXMLNode( rapidxml::xml_node<>* xml_node )
{
	std::shared_ptr<CDatabaseTableInfo> table(new CDatabaseTableInfo);

	// 加载表单信息;
	auto xml_node_table = xml_node->first_node("table");
	if(xml_node_table) {
		table->set_name(sRapidXML->GetAttribute(xml_node_table, "name", table->name()));
	}

	// 加载字段信息;
	auto xml_node_cols = xml_node_table->first_node("cols");
	if(xml_node_cols) {

		auto xml_node_col = xml_node_cols->first_node("col");
		while(xml_node_col) {

			CDatabaseColInfo col;
			col.set_name(sRapidXML->GetAttribute(xml_node_col, "name", col.name()));
			col.set_type(ColTypeName2Type(sRapidXML->GetAttribute(xml_node_col, "type", "")));
			col.set_char_size(sRapidXML->GetAttribute(xml_node_col, "char_size", col.char_size()));
			table->col_info_vector().push_back(col);

			xml_node_col = xml_node_col->next_sibling("col");
		}
	}

	// 加载索引信息;
	auto xml_node_keys = xml_node_table->first_node("keys");
	if(xml_node_keys) {

		auto xml_node_key = xml_node_keys->first_node("key");
		while(xml_node_key) {

			CDatabaseIndexInfo index_info;
			index_info.set_name(sRapidXML->GetAttribute(xml_node_key, "name", index_info.name()));

			std::string col_name_array_str;
			util::CString::Split<util::CCharsetUTF8>(sRapidXML->GetAttribute(xml_node_key, "col_name", col_name_array_str), 
				",", 
				index_info.col_name_array());

			index_info.set_is_primary_key(sRapidXML->GetAttribute(xml_node_key, "primary_key", index_info.is_primary_key()));
			table->index_info_vector().push_back(index_info);

			xml_node_key = xml_node_key->next_sibling("key");
		}
	}
	return table;
}

std::shared_ptr<CDatabaseTableInfo> CDatabaseTableInfoLoader::LoadTableInfoFromFile( const std::string& file_name )
{
	// 加载配置;
	rapidxml::file<> fdoc(file_name.c_str());
	if(fdoc.data() == 0) {

		sLogError("%s is not exists!", file_name.c_str());
		return std::shared_ptr<CDatabaseTableInfo>();
	}

	// 解析配置;
	rapidxml::xml_document<> doc;
	try {
		doc.parse<0>(fdoc.data(), fdoc.size());
	}
	catch (...) {

		sLogError("%s parse error!", file_name.c_str());
		return std::shared_ptr<CDatabaseTableInfo>();
	}
	return LoadTableFromXMLNode(&doc);
}

NS_DS_END