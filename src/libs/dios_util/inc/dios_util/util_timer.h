#ifndef __DS_UTIL_TIMER_H__
#define __DS_UTIL_TIMER_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

class DS_UTIL_DECL CTimer{
public:
	static ds_uint64 GetMicroSecond( void );
	static ds_uint32 GetMilliSecond( void );
};

/**
* 设置interval_值，更新刷新增加current_，当current_>=interval_就passed了。
* 此功能用于：间隔循环调用型，自动设置保存间隔，只需Reset即可循环调用。
*    1. some_timer.set_interval(40)
*    2. some_timer.update(eapsed_time)
*    3. if(some_timer.isPassed()) { DoLoopThing(); some_timer.reset()}
*/
class DS_UTIL_DECL CIntervalTimer
{
public:
	CIntervalTimer();

	void Update( ds_uint32 diff);
	bool IsPassed();
	void Reset();

	DS_PROPERTY(ds_uint32, interval);
	DS_PROPERTY_READONLY(ds_int32, current);
};

/** 期满定时器;
* 设置expiry_time值，更新刷新减少expiry_time，当expiry_time<=0就passed了。[expiry:终止，期满]
* 此功能用于：过期时间调用型，想再调用需要重设过期时间;
*    1. some_timer.set_expiry_time(40)
*    2. some_timer.Update(eapsed_time)
*    3. if(some_timer.Passed()) { DoLoopThing(); some_timer.Reset(40)}
*/
class DS_UTIL_DECL CExpiryTimer
{
public:
	CExpiryTimer(ds_uint32 expiry);

	void Update(ds_uint32 diff);
	bool IsPassed(void) const;
	void Reset(ds_uint32 expiry_time);

	DS_PROPERTY(ds_uint32, expiry_time);
};

/** 逝去定时器;
* 距离上次时间调用逝去多少时间;
*/
class DS_UTIL_DECL CElapsedTimer		{
public:

	CElapsedTimer();
	ds_uint32	GetElapsedTime(ds_boolean reset=true);
private:
	ds_uint32 time_begin_;

};

NS_UTIL_END
NS_DS_END
#endif // __DS_TIMER_H__
