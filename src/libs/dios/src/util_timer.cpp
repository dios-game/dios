
#include "precompiled.h"
#include "util_timer.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

#if ( DIOS_TARGET_PLATFORM == DIOS_PLATFORM_WIN32 )
class WinMicroTimer
{
public:
	WinMicroTimer( void ) {
		QueryPerformanceFrequency( (LARGE_INTEGER*)(&m_frequency) );
		m_frequency = m_frequency / 1000000;
	}

	inline dios_uint64 getMicroSecond( void ) {
		dios_uint64 t;
		QueryPerformanceCounter((LARGE_INTEGER*)(&t));
		return (t / m_frequency);
	}
private:
	dios_uint64	m_frequency;
};

dios_uint64 CTimer::GetMicroSecond( void )
{
	static WinMicroTimer win_micro_timer;
	return win_micro_timer.getMicroSecond();
}

dios_uint32 CTimer::GetMilliSecond( void )
{
	struct _timeb tb;
	_ftime(&tb);
	return ((tb.time&0x003FFFFF)*1000)+tb.millitm;
}

#else
dios_uint64 CTimer::GetMicroSecond( void )
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}

dios_uint32 CTimer::GetMilliSecond( void )
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif

CIntervalTimer::CIntervalTimer() : interval_(0), current_(0)
{

}

void CIntervalTimer::Update( dios_uint32 diff )
{
	current_ += diff; if(current_<0) current_=0;
}

bool CIntervalTimer::IsPassed()
{
	return current_ >= interval_;
}

void CIntervalTimer::Reset()
{
	if(current_ >= interval_) current_ -= interval_;
}

CExpiryTimer::CExpiryTimer( dios_uint32 expiry ) : expiry_time_(expiry)
{

}

void CExpiryTimer::Update( dios_uint32 diff )
{
	if(expiry_time_){
		expiry_time_ -= diff;
		if(expiry_time_<0){
			expiry_time_ = 0;
		}
	}
}

bool CExpiryTimer::IsPassed( void ) const
{
	return (expiry_time_ <= 0);
}

void CExpiryTimer::Reset( dios_uint32 expiry_time )
{
	expiry_time_ = expiry_time;
}

CElapsedTimer::CElapsedTimer()
{
	time_begin_ = CTimer::GetMilliSecond();
}

dios_uint32 CElapsedTimer::GetElapsedTime(dios_boolean reset/*=true*/)
{
	dios_uint32 time_end = CTimer::GetMilliSecond();
	dios_uint32 rlt = time_end - time_begin_;
	if(reset){
		time_begin_ = time_end;
	}
	return rlt;
}

NS_UTIL_END
NS_DIOS_END
