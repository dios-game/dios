#ifndef _____TASK_SERVICE_H_________
#define _____TASK_SERVICE_H_________

#include "dios/platform.h"
#include "dios_com/dios_com.h"

NS_DS_BEGIN

namespace com {

	typedef std::function<void()> TaskCallBack;

	/*
	 *	时间任务：可以进行延时，循环等操作的任务;
	 */
	class ITimerTask
	{
	public:
		typedef std::shared_ptr<ITimerTask> Ptr;

		virtual ~ITimerTask(void) {}

		// 投递时间任务;
		virtual ds_boolean Post(TaskCallBack callback, ds_uint32 milliseconds, ds_boolean is_repeat) = 0;

		// 重新投递当前时间任务;
		virtual ds_boolean Post(ds_uint32 milliseconds, ds_boolean is_repeat) = 0;

		// 取消正在进行的时间任务;
		virtual void Cancel(void) = 0;
	};

	/*
	 *	串型任务：该对象投递的任务是串型的;
	 */
	class IStrandTask
	{
	public:
		typedef std::shared_ptr<IStrandTask> Ptr;

		virtual ~IStrandTask(void) {}

		// 投递任务;
		virtual void Post(const TaskCallBack& callback) = 0;

		// 创建串型时间任务;
		virtual ITimerTask::Ptr CreateTimeTask(void) = 0;
	};

	/*
	 *	任务服务;
	 */
	class ITaskService : public ICom
	{
	public:
		typedef std::shared_ptr<ITaskService> Ptr;

		virtual ~ITaskService(void) {}

		// 设置任务服务的线程数;
		virtual void set_thread_count(ds_uint32 thread_count) = 0;

		// 投递任务;
		virtual void Post(TaskCallBack callback) = 0; 

		// 创建串型任务;
		virtual IStrandTask::Ptr CreateStrandTask(void) = 0;

		// 创建时间任务;
		virtual ITimerTask::Ptr CreateTimerTask(void) = 0;
	};

}

NS_DS_END

#endif