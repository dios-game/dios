#ifndef DIOS_DB_TABLEINFO_LOADER_H
#define DIOS_DB_TABLEINFO_LOADER_H

#include "dios_db_table_lib.h"

#include "dios/platform.h"
#include "rapidxml/rapidxml.hpp"

#include "dios_db_tableinfo.h"

NS_DS_BEGIN

/*
*	表信息加载器;
*/
class DIOS_DB_TABLE_DECL CDatabaseTableInfoLoader
{
public:
	CDatabaseTableInfoLoader(void);
	~CDatabaseTableInfoLoader(void);

	// 字符串转换为类型枚举;
	DatabaseColType ColTypeName2Type(const std::string& name);

	// 解析为DBTable;
	std::shared_ptr<CDatabaseTableInfo> LoadTableFromXMLNode(rapidxml::xml_node<>* xml_node);
	std::shared_ptr<CDatabaseTableInfo> LoadTableInfoFromFile(const std::string& file_name);

	DS_SINGLETON(CDatabaseTableInfoLoader);
};

NS_DS_END

#define sDatabaseTableLoader CDatabaseTableLoader::GetInstancePtr()

#endif