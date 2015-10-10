#ifndef UTIL_BOOST_SCHEDULE_H
#define UTIL_BOOST_SCHEDULE_H

#include "dios_util_boost_lib.h"

#include <map>
#include "dios_util/util_time.h"
#include "dios_util/util_event_set.hpp"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 *	定点时间瞬时任务;
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

	// 初始化;
	void Init(int period, 
		std::function<void(ds_int32)> callback, 
		const dios::util::CTime& start_time, 
		const dios::util::CTime& last_update_time);

	// 更新;
	void Update(const dios::util::CTime& current_time);

	// 属性获取;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, start_time);
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, current_time);
	DS_PROPERTY_READONLY(ds_int32, period);

	/// \brief void Callback(ds_boolean execute_times); 参数(execute_times)期间更新几次;
	DS_PROPERTY_READONLY(std::function<void(ds_int32)>, callback);

	DS_REF_PROPERTY(dios::util::CEvent<void()>, schedule_state_changed_event); // 下次启动时间变更事件;
};

/*
*	定点时间时长任务;
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

	// 初始化;
	void Init(int period, 
		std::function<void(ds_boolean)> start_callback, 
		std::function<void()> stop_callback, 
		const dios::util::CTime& start_time,
		const dios::util::CTime& stop_time,
		const dios::util::CTime& last_update_time,
		ds_boolean last_running);

	// 更新;
	void Update(const dios::util::CTime& current_time);

	// 属性获取;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, start_time); // 下次起始时间;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, stop_time); // 关闭时间;
	DS_PROPERTY_READONLY_PASS_BY_REF(dios::util::CTime, current_time); // 最后一次更新时间;
	DS_PROPERTY_READONLY(ds_int32, period); // 时间间隔;
	DS_PROPERTY(std::function<void()>, stop_callback); // 关闭回调;

	DS_PROPERTY_READONLY(ds_boolean, running); // 是否进行中;
	DS_PROPERTY_READONLY(ds_boolean, update_fixed); // 更新已经修正;

	/// \brief void Callback(ds_boolean is_new_period); 参数(is_new_period)表示是否新周期;
	DS_PROPERTY(std::function<void(ds_boolean)>, start_callback);

	DS_REF_PROPERTY(dios::util::CEvent<void()>, schedule_state_changed_event); // 状态变更事件;

private:
	void _FixUpdate();
};

NS_UTIL_BOOST_END
NS_DS_END

#endif