
#include "precompiled.h"
#include "util_timer.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

#if ( DS_TARGET_PLATFORM == DS_PLATFORM_WIN32 )
class WinMicroTimer
{
public:
	WinMicroTimer( void ) {
		QueryPerformanceFrequency( (LARGE_INTEGER*)(&m_frequency) );
		m_frequency = m_frequency / 1000000;
	}

	inline ds_uint64 getMicroSecond( void ) {
		ds_uint64 t;
		QueryPerformanceCounter((LARGE_INTEGER*)(&t));
		return (t / m_frequency);
	}
private:
	ds_uint64	m_frequency;
};

ds_uint64 CTimer::GetMicroSecond( void )
{
	static WinMicroTimer win_micro_timer;
	return win_micro_timer.getMicroSecond();
}

ds_uint32 CTimer::GetMilliSecond( void )
{
	struct _timeb tb;
	_ftime(&tb);
	return ((tb.time&0x003FFFFF)*1000)+tb.millitm;
}

#else
ds_uint64 CTimer::GetMicroSecond( void )
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}

ds_uint32 CTimer::GetMilliSecond( void )
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif


ds_int64 CElapsedTimer::GetElapsedHours() const
{
	return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

ds_int64 CElapsedTimer::GetElapsedMinutes() const
{
	return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

ds_int64 CElapsedTimer::GetElapsedSeconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

ds_int64 CElapsedTimer::GetElapsedNano() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

ds_int64 CElapsedTimer::GetElapsedMicro() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

double CElapsedTimer::GetElapsed() const
{
	return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_begin).count();
}

void CElapsedTimer::Reset()
{
	m_begin = std::chrono::high_resolution_clock::now();
}

CElapsedTimer::CElapsedTimer() : m_begin(std::chrono::high_resolution_clock::now())
{

}

NS_UTIL_END
NS_DS_END
