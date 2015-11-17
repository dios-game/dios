/************************************************************************/
/* 
	数据库表单创建;
 */
/************************************************************************/

#ifndef DIOS_DB_TABLE_CREATOR_H
#define DIOS_DB_TABLE_CREATOR_H

#include "dios/platform.h"

#include "component/com_sql.h"
#include "dios_db_tableinfo.h"

NS_DS_BEGIN

/*
 *	表创建器;
 */
class DIOS_DB_TABLE_DECL CDatabaseTableCreator
{
public:
	
	// 创建表信息;
	ds_boolean CreateTable(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	DS_SINGLETON(CDatabaseTableCreator);

private:
	
	// 创建表的字段信息;
	ds_boolean _CreateCol(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	// 创建表的索引信息;
	ds_boolean _CreateIndex(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	// 创建表的外键信息;
	ds_boolean _CreateForeignKey(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);
};

NS_DS_END

#define sDatabaseTableCreator dios::CDatabaseTableCreator::GetInstancePtr()

#endif
