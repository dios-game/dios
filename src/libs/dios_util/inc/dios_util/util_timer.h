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
* ����interval_ֵ������ˢ������current_����current_>=interval_��passed�ˡ�
* �˹������ڣ����ѭ�������ͣ��Զ����ñ�������ֻ��Reset����ѭ�����á�
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

/** ������ʱ��;
* ����expiry_timeֵ������ˢ�¼���expiry_time����expiry_time<=0��passed�ˡ�[expiry:��ֹ������]
* �˹������ڣ�����ʱ������ͣ����ٵ�����Ҫ�������ʱ��;
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

/** ��ȥ��ʱ��;
* �����ϴ�ʱ�������ȥ����ʱ��;
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
