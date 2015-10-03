#ifndef __DS_UTIL_TIMER_H__
#define __DS_UTIL_TIMER_H__

#include "dios_util_lib.h"

#include <chrono>

NS_DS_BEGIN
NS_UTIL_BEGIN

class DS_UTIL_DECL CTimer{
public:
	static ds_uint64 GetMicroSecond( void );
	static ds_uint32 GetMilliSecond( void );
};

/** ��ȥ��ʱ��;
* �����ϴ�ʱ�������ȥ����ʱ��;
*/
class DS_UTIL_DECL CElapsedTimer{
public:
	CElapsedTimer(); 
	void Reset();	 
	//Ĭ�������;
	double GetElapsed() const;	
	//΢��;
	ds_int64 GetElapsedMicro() const; 
	//����;
	ds_int64 GetElapsedNano() const; 
	//��;
	ds_int64 GetElapsedSeconds() const;	 
	//��;
	ds_int64 GetElapsedMinutes() const;	 
	//ʱ;
	ds_int64 GetElapsedHours() const;  
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

NS_UTIL_END
NS_DS_END
#endif // __DS_TIMER_H__
