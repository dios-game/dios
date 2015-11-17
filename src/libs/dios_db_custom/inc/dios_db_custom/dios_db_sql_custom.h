#ifndef DIOS_DB_SQL_CUSTOM_H
#define DIOS_DB_SQL_CUSTOM_H

#include "dios_db_custom_lib.h"

#include "component/com_task.h"
#include "dios_db_table/dios_db_table_creator.h"
#include "dios_db_custom.h"

NS_DS_BEGIN

/*
 *	自定义代码规范;
 */
class DIOS_DB_CUSTOM_DECL IDatabaseSqlCommitRecord
{
public:
	typedef std::shared_ptr<IDatabaseSqlCommitRecord> Ptr;

	virtual bool IsDirty(void) = 0;
	virtual bool CommitInsert(com::ISqlConnector::Ptr sql_connector) = 0;
	virtual bool CommitUpdate(com::ISqlConnector::Ptr sql_connector) = 0;
	virtual bool CommitDelete(com::ISqlConnector::Ptr sql_connector) = 0;
};

class DIOS_DB_CUSTOM_DECL CDatabaseSqlCommitTool
{
public:
	CDatabaseSqlCommitTool(void);
	~CDatabaseSqlCommitTool(void);

	void CommitInsert(IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func);
	void CommitUpdate(IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func);
	void CommitDelete(IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func);

protected:
	com::IStrandTask::Ptr strand_task_;
};

extern "C" {
	DIOS_DB_CUSTOM_DECL void BaseDatabaseSqlCreateTable(const std::string& dest_id, CDatabaseCustomTable* info, std::function<void(ds_boolean)> func);
	DIOS_DB_CUSTOM_DECL void BaseDatabaseSqlSelectRecordSet(const std::string& dest_id, std::function<void(com::ISqlConnector::Ptr)> func);
};

NS_DS_END

#endif
