#include "precompiled.h"
#include "util_time.h"


ds_uint64 dios::util::CTime::NowTime(void)
{
	time_t time_sec; 

#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)  
	time_sec = time(0); 
#else  
	struct timeval now;  
	gettimeofday(&now, NULL);  
	time_sec = now.tv_sec; 
#endif
	return time_sec;
}

ds_uint64 dios::util::CTime::ToTime(std::string date_time_string)
{
	struct tm tm; 

#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)  
	SYSTEMTIME xSys;
	memset(&xSys,0,sizeof(SYSTEMTIME));
	sscanf(date_time_string.c_str(),"%hu-%hu-%hu %hu:%hu:%hu",&xSys.wYear,&xSys.wMonth,&xSys.wDay,&xSys.wHour,&xSys.wMinute,&xSys.wSecond);
	tm.tm_year = xSys.wYear - 1900;
	tm.tm_mon = xSys.wMonth - 1;
	tm.tm_mday = xSys.wDay;
	tm.tm_hour = xSys.wHour;
	tm.tm_min = xSys.wMinute;
	tm.tm_sec = xSys.wSecond;
	tm.tm_wday = xSys.wDayOfWeek;
	tm.tm_isdst = _daylight;
#else
	strptime(date_time_string.c_str(), "%Y-%m-%d %H:%M:%S" , &tm); 
#endif // (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)  

	return mktime(&tm);
}

std::string dios::util::CTime::ToTimeSpanString(ds_int64 time_span)
{
	char buff[128] = {0};
	sprintf(buff, "%02lld:%02lld:%02lld", time_span/(60*60),(time_span/60)%60, time_span%60);
	return buff;
}

std::string dios::util::CTime::ToDateTimeString(ds_uint64 time)
{
	time_t time_v = time;
	struct tm *tm; 
	tm = localtime(&time_v); 
	char buff[128] = {0};
	int nSize = strftime(buff,128,"%Y-%m-%d %H:%M:%S",tm);
	return buff;
// 	int year = tm->tm_year + 1900; 
// 	int month = tm->tm_mon + 1; 
// 	int day = tm->tm_mday; 
// 	int hour= tm->tm_hour; 
// 	int min= tm->tm_min; 
// 	int second= tm->tm_sec;
//  sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", );
}

std::string dios::util::CTime::ToTimeString(ds_uint64 time)
{
	time_t time_v = time;
	struct tm *tm; 
	tm = localtime(&time_v); 
	char buff[128] = {0};
	int nSize = strftime(buff,128,"%H:%M:%S",tm);
	return buff;
}

std::string dios::util::CTime::ToDateString(ds_uint64 time)
{
	time_t time_v = time;
	struct tm *tm; 
	tm = localtime(&time_v); 
	char buff[128] = {0};
	int nSize = strftime(buff,128,"%Y-%m-%d",tm);
	return buff;
}

ds_int64 dios::util::CTime::DiffTime(ds_uint64 time1, ds_uint64 time2)
{
	return time1 - time2;
}