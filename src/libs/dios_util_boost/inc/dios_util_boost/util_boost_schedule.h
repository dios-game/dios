#ifndef UTIL_BOOST_SCHEDULE_H
#define UTIL_BOOST_SCHEDULE_H

#include "dios_util_boost_lib.h"

#include <map>
#include "dios_util/util_time.h"
#include "dios_util/util_event_set.hpp"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 *	����ʱ��˲ʱ����;
 dios::util_boost::CScheduleHandle1 schedule;
 dios::util_boost::CTime last_update_time_db("2015-01-12 12:00:00");
 schedule.Init(86400, [](ds_int32 times){ }, dios::util_boost::CTime("2015-01-12 12:00:00"), last_update_time_db);
 schedule.schedule_state_changed_event().Connect([&last_update_time_db, schedule](){ last_update_time_db.Reset(schedule.current_time());});
 schedule.Update(dios::util_boost::CTime::Now());
 */
class DIOS_UTIL_BOOST_DECL CScheduleHandle1
{
public:
	typedef std::shared_ptr<CScheduleHandle1> Ptr;

	CScheduleHandle1(void);
	~CScheduleHandle1(void);

	// ��ʼ��;
	void Init(int period, 
		std::function<void(ds_int32)> callback, 
		const dios::util::CTime& start_time, 
		const dios::util::CTime& last_update_time);

	// ����;
	void Update(const dios::util::CTime& current_time);

	// ���Ի�ȡ;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, start_time);
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, current_time);
	DS_PROPERTY_READONLY(ds_int32, period);

	/// \brief void Callback(ds_boolean execute_times); ����(execute_times)�ڼ���¼���;
	DS_PROPERTY_READONLY(std::function<void(ds_int32)>, callback);

	DS_REF_PROPERTY(dios::util::CEvent<void()>, schedule_state_changed_event); // �´�����ʱ�����¼�;
};

/*
*	����ʱ��ʱ������;
dios::util_boost::CScheduleHandle2 schedule;
dios::util_boost::CTime last_update_time_db("2015-01-12 12:00:00");
ds_boolean is_starting_db = false;;
schedule.Init(86400, [](ds_boolean is_new_period){ }, [](){},
dios::util_boost::CTime("2015-01-12 12:00:00"), 
dios::util_boost::CTime("2015-01-12 12:15:00"), 
last_start_time_db,is_starting_db);
schedule.schedule_state_changed_event().Connect([&last_start_time_db, &is_starting_db, schedule](){ last_update_time_db.Reset(schedule.current_time()); is_starting_db=schedule.starting();});
schedule.Update(dios::util_boost::CTime::Now());
*/
class DIOS_UTIL_BOOST_DECL CScheduleHandle2
{
public:
	typedef std::shared_ptr<CScheduleHandle2> Ptr;

	CScheduleHandle2(void);
	~CScheduleHandle2(void);

	// ��ʼ��;
	void Init(int period, 
		std::function<void(ds_boolean)> start_callback, 
		std::function<void()> stop_callback, 
		const dios::util::CTime& start_time,
		const dios::util::CTime& stop_time,
		const dios::util::CTime& last_update_time,
		ds_boolean last_running);

	// ����;
	void Update(const dios::util::CTime& current_time);

	// ���Ի�ȡ;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, start_time); // �´���ʼʱ��;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, stop_time); // �ر�ʱ��;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, current_time); // ���һ�θ���ʱ��;
	DS_PROPERTY_READONLY(ds_int32, period); // ʱ����;
	DS_PROPERTY(std::function<void()>, stop_callback); // �رջص�;

	DS_PROPERTY_READONLY(ds_boolean, running); // �Ƿ������;
	DS_PROPERTY_READONLY(ds_boolean, update_fixed); // �����Ѿ�����;

	/// \brief void Callback(ds_boolean is_new_period); ����(is_new_period)��ʾ�Ƿ�������;
	DS_PROPERTY(std::function<void(ds_boolean)>, start_callback);

	DS_REF_PROPERTY(dios::util::CEvent<void()>, schedule_state_changed_event); // ״̬����¼�;

private:
	void _FixUpdate();
};

NS_UTIL_BOOST_END
NS_DS_END

#endif