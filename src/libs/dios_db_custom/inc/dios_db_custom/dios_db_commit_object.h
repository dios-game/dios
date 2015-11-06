#ifndef DIOS_DB_COMMIT_OBJECT_H
#define DIOS_DB_COMMIT_OBJECT_H

#include "dios_db_custom_lib.h"

#include "dios/platform.h"

NS_DS_BEGIN

// �ύ״̬;
enum DatabaseCommitStatus
{
	kDatabaseCommitStatusNone,
	kDatabaseCommitStatusInsert,
	kDatabaseCommitStatusUpdate,
	kDatabaseCommitStatusDelete,
};

/*
 *	�����ύ����;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCommitObject
{
public:
	CDatabaseCommitObject(void);
	CDatabaseCommitObject(DatabaseCommitStatus commit_status);
	virtual ~CDatabaseCommitObject(void);

	inline DatabaseCommitStatus commit_status(void) { return commit_status_; }

	// �ύ����;
	void Commit(std::function<void(ds_boolean)> func);

	// ɾ����¼����;
	void set_deleted(void);

	// �Ƿ��Ѿ�ɾ��;
	ds_boolean is_deleted(void);

	// �ύ����;
	virtual void CommitInsert(std::function<void(ds_boolean)> func) {}
	virtual void CommitUpdate(std::function<void(ds_boolean)> func) {}
	virtual void CommitDelete(std::function<void(ds_boolean)> func) {}

protected:
	DatabaseCommitStatus commit_status_;
};

NS_DS_END

#endif