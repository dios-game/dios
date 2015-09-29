#include "precompiled.h"
#include <stdio.h>

#include <map>

#include "boost/thread.hpp"

#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"			
#include "boost/date_time/posix_time/posix_time.hpp"

#include "crash_handler/crash_handler.h"


#if DS_TARGET_PLATFORM==DS_PLATFORM_WIN32

#include "http.h"
void TestHttp(){

	CHttpServiceImpl http;
	std::string result;
	http.GetUrlData("http://www.baidu.com", result);
	printf("baidu %s\n", result.c_str());
}
#else

void TestHttp(){

}
#endif

//static
std::string NowString()
{
	std::string str = boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time());

	// 'T'替换为空格符;
	int index_T = str.find("T");
	if (index_T != std::string::npos) {
		str.replace(index_T, 1, " ");
	}

	// 删除小数点后的字符;
	int index_dot = str.find(".");
	if (index_dot != std::string::npos) {
		str.erase(index_dot);
	}
	return str;
}

#define DS_DOT ,
int main(int argc, char **argv)
{
	std::string dump_folder = "dump";
	std::string svn_version = "11";
	dump_folder += svn_version;

	CMyCrash::Install(dump_folder.c_str());

	std::map<int DS_DOT int> map_test;
	map_test[1] = 10;
	printf("hello world %d\n", map_test[1]);

	boost::thread thread([](){ printf("%s hello thread\n", NowString().c_str()); });
	thread.join();
	printf("%s hello world %d\n", NowString().c_str());

	TestHttp();
}
