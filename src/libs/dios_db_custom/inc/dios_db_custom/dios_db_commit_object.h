#ifndef DIOS_DB_COMMIT_OBJECT_H
#define DIOS_DB_COMMIT_OBJECT_H

#include "dios_db_custom_lib.h"

#include "dios/platform.h"

NS_DS_BEGIN

// 提交状态;
enum DatabaseCommitStatus
{
	kDatabaseCommitStatusNone,
	kDatabaseCommitStatusInsert,
	kDatabaseCommitStatusUpdate,
	kDatabaseCommitStatusDelete,
};

/*
 *	数据提交对象;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCommitObject
{
public:
	CDatabaseCommitObject(void);
	CDatabaseCommitObject(DatabaseCommitStatus commit_status);
	virtual ~CDatabaseCommitObject(void);

	inline DatabaseCommitStatus commit_status(void) { return commit_status_; }

	// 提交函数;
	void Commit(std::function<void(ds_boolean)> func);

	// 删除记录函数;
	void set_deleted(void);

	// 是否已经删除;
	ds_boolean is_deleted(void);

	// 提交函数;
	virtual void CommitInsert(std::function<void(ds_boolean)> func) {}
	virtual void CommitUpdate(std::function<void(ds_boolean)> func) {}
	virtual void CommitDelete(std::function<void(ds_boolean)> func) {}

protected:
	DatabaseCommitStatus commit_status_;
};

NS_DS_END

#endif