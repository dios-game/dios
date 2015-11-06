#ifndef _____TASK_SERVICE_H_________
#define _____TASK_SERVICE_H_________

#include "dios/platform.h"
#include "dios_com/dios_com.h"

NS_DS_BEGIN

namespace com {

	typedef std::function<void()> TaskCallBack;

	/*
	 *	ʱ�����񣺿��Խ�����ʱ��ѭ���Ȳ���������;
	 */
	class ITimerTask
	{
	public:
		typedef std::shared_ptr<ITimerTask> Ptr;

		virtual ~ITimerTask(void) {}

		// Ͷ��ʱ������;
		virtual ds_boolean Post(TaskCallBack callback, ds_uint32 milliseconds, ds_boolean is_repeat) = 0;

		// ����Ͷ�ݵ�ǰʱ������;
		virtual ds_boolean Post(ds_uint32 milliseconds, ds_boolean is_repeat) = 0;

		// ȡ�����ڽ��е�ʱ������;
		virtual void Cancel(void) = 0;
	};

	/*
	 *	�������񣺸ö���Ͷ�ݵ������Ǵ��͵�;
	 */
	class IStrandTask
	{
	public:
		typedef std::shared_ptr<IStrandTask> Ptr;

		virtual ~IStrandTask(void) {}

		// Ͷ������;
		virtual void Post(const TaskCallBack& callback) = 0;

		// ��������ʱ������;
		virtual ITimerTask::Ptr CreateTimeTask(void) = 0;
	};

	/*
	 *	�������;
	 */
	class ITaskService : public ICom
	{
	public:
		typedef std::shared_ptr<ITaskService> Ptr;

		virtual ~ITaskService(void) {}

		// �������������߳���;
		virtual void set_thread_count(ds_uint32 thread_count) = 0;

		// Ͷ������;
		virtual void Post(TaskCallBack callback) = 0; 

		// ������������;
		virtual IStrandTask::Ptr CreateStrandTask(void) = 0;

		// ����ʱ������;
		virtual ITimerTask::Ptr CreateTimerTask(void) = 0;
	};

}

NS_DS_END

#endif