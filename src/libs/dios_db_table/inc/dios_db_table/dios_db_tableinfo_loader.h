#ifndef DIOS_DB_TABLEINFO_LOADER_H
#define DIOS_DB_TABLEINFO_LOADER_H

#include "dios_db_table_lib.h"

#include "dios/platform.h"
#include "rapidxml/rapidxml.hpp"

#include "dios_db_tableinfo.h"

NS_DS_BEGIN

/*
*	����Ϣ������;
*/
class DIOS_DB_TABLE_DECL CDatabaseTableInfoLoader
{
public:
	CDatabaseTableInfoLoader(void);
	~CDatabaseTableInfoLoader(void);

	// �ַ���ת��Ϊ����ö��;
	DatabaseColType ColTypeName2Type(const std::string& name);

	// ����ΪDBTable;
	std::shared_ptr<CDatabaseTableInfo> LoadTableFromXMLNode(rapidxml::xml_node<>* xml_node);
	std::shared_ptr<CDatabaseTableInfo> LoadTableInfoFromFile(const std::string& file_name);

	DS_SINGLETON(CDatabaseTableInfoLoader);
};

NS_DS_END

#define sDatabaseTableLoader CDatabaseTableLoader::GetInstancePtr()

#endif