/************************************************************************/
/* 
	���ݿ������;
 */
/************************************************************************/

#ifndef DIOS_DB_TABLE_CREATOR_H
#define DIOS_DB_TABLE_CREATOR_H

#include "dios/platform.h"

#include "component/com_sql.h"
#include "dios_db_tableinfo.h"

NS_DS_BEGIN

/*
 *	������;
 */
class DIOS_DB_TABLE_DECL CDatabaseTableCreator
{
public:
	
	// ��������Ϣ;
	ds_boolean CreateTable(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	DS_SINGLETON(CDatabaseTableCreator);

private:
	
	// ��������ֶ���Ϣ;
	ds_boolean _CreateCol(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	// �������������Ϣ;
	ds_boolean _CreateIndex(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);

	// ������������Ϣ;
	ds_boolean _CreateForeignKey(com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info);
};

NS_DS_END

#define sDatabaseTableCreator dios::CDatabaseTableCreator::GetInstancePtr()

#endif
