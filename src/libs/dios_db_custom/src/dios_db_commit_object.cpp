#include "precompiled.h"
#include "dios_db_commit_object.h"

NS_DS_BEGIN

CDatabaseCommitObject::CDatabaseCommitObject( void )
{ 
	commit_status_ = kDatabaseCommitStatusInsert;
}

CDatabaseCommitObject::CDatabaseCommitObject( DatabaseCommitStatus commit_status )
{
	commit_status_ = commit_status;
}

CDatabaseCommitObject::~CDatabaseCommitObject( void )
{

}

void CDatabaseCommitObject::Commit( std::function<void(ds_boolean)> func )
{
	switch(commit_status_)
	{
	case kDatabaseCommitStatusInsert:
		{
			CommitInsert(func);
			commit_status_ = kDatabaseCommitStatusUpdate;
		}
		break;
	case kDatabaseCommitStatusUpdate:
		{
			CommitUpdate(func);
		}
		break;
	case kDatabaseCommitStatusDelete:
		{
			CommitDelete(func);
			commit_status_ = kDatabaseCommitStatusNone;
		}
		break;
	}
}

void CDatabaseCommitObject::set_deleted( void ) 
{
	if(commit_status_ != kDatabaseCommitStatusNone) {
		commit_status_ = kDatabaseCommitStatusDelete;
	}
}

bool CDatabaseCommitObject::is_deleted( void )
{
	return (commit_status_ == kDatabaseCommitStatusDelete);
}

NS_DS_END
