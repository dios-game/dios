#include "precompiled.h"
#include "util_boost_schedule.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

CScheduleHandle1::CScheduleHandle1( void )
{
	
}

CScheduleHandle1::~CScheduleHandle1( void )
{

}

void CScheduleHandle1::Init( int period, 
	std::function<void(ds_int32)> callback, 
	const dios::util::CTime& start_time,
	const dios::util::CTime& last_update_time)
{
	period_ = period==0?1:period;
	callback_ = callback;
	start_time_ = start_time;
	current_time_ = last_update_time;

	if(current_time_ >= start_time_) {

		dios::util::CTimeSpan time_span(((current_time_ - start_time_).GetSeconds() / period_ + 1)*period_);
		start_time_ += time_span;
	}
}

void CScheduleHandle1::Update(const dios::util::CTime& current_time)
{
	current_time_ = current_time;

	// 更新时间;
	dios::util::CTime start_time = start_time_;
	int times = 0;
	if(current_time_ >= start_time) {
		
		times = (current_time_ - start_time).GetSeconds()/period_+1;
		dios::util::CTimeSpan time_span(times*period_);
		start_time += time_span;
	}

	// 执行回调;
	if(start_time_ != start_time) {

		if(callback_) {
			callback_(times);
		}
		start_time_ = start_time;
		schedule_state_changed_event_();
	}
}

CScheduleHandle2::CScheduleHandle2( void )
{
	update_fixed_ = true;
	running_= false;
}

CScheduleHandle2::~CScheduleHandle2( void )
{

}

void CScheduleHandle2::Init( int period, 
	std::function<void(ds_boolean)> start_callback, 
	std::function<void()> stop_callback, 
	const dios::util::CTime& start_time,
	const dios::util::CTime& stop_time,
	const dios::util::CTime& last_update_time,
	ds_boolean last_running
	)
{
	period_ = period==0?1:period;
	start_callback_ = start_callback;
	stop_callback_ = stop_callback;
	start_time_ = start_time;
	stop_time_ = stop_time;
	current_time_ = last_update_time;

	if(current_time_ >= stop_time_) {

		dios::util::CTimeSpan time_span(((current_time_ - stop_time_).GetSeconds() / period_ + 1)*period_);
		start_time_ += time_span;
		stop_time_ += time_span;
	}

	running_ = last_running;
}

void CScheduleHandle2::Update(const dios::util::CTime& current_time)
{
	current_time_ = current_time;

	// 调整到执行周期;
	if(update_fixed_){
		_FixUpdate();
		update_fixed_ = false;
	}

	// 检查调用回调;
	if(running_){
		if(current_time_ >= stop_time_) {

			if(stop_callback_) {
				stop_callback_();
			}

			dios::util::CTimeSpan time_span(((current_time_ - stop_time_).GetSeconds() / period_ + 1)*period_);
			start_time_ += time_span;
			stop_time_ += time_span;
			running_ = false;
			schedule_state_changed_event_();
		}
	}

	// 运行周期回调;
	if(!running_){
		if(current_time_ >= start_time_) {

			if(start_callback_) {
				start_callback_(true);
			}
			running_ = true;
			schedule_state_changed_event_();
		}
	}
}

void CScheduleHandle2::_FixUpdate()
{
	if(current_time_ >= stop_time_) {

		if(running_){
			if(start_callback_) {
				start_callback_(false);
			}
			if(stop_callback_) {
				stop_callback_();
			}
			running_ = false;
		}

		dios::util::CTimeSpan time_span(((current_time_ - stop_time_).GetSeconds() / period_ + 1)*period_);
		start_time_ += time_span;
		stop_time_ += time_span;

		if(current_time_ >= start_time_) {
			if(start_callback_) {
				start_callback_(true);
			}
			running_ = true;
		}
		schedule_state_changed_event_();
	}
	else{
		if(current_time_ >= start_time_) {
			if(start_callback_) {
				start_callback_(!running_);
			}
			running_ = true;
		}
		schedule_state_changed_event_();
	}
}


NS_UTIL_BOOST_END
NS_DS_END
