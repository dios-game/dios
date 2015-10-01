#include "precompiled.h"
#include <stdio.h>
#include "boost/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

//static
static std::string NowString()
{
	std::string str = boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time());

	// 'T'�滻Ϊ�ո��;
	int index_T = str.find("T");
	if (index_T != std::string::npos) {
		str.replace(index_T, 1, " ");
	}

	// ɾ��С�������ַ�;
	int index_dot = str.find(".");
	if (index_dot != std::string::npos) {
		str.erase(index_dot);
	}
	return str;
}

int main(int argc, char **argv)
{
	boost::thread thread([](){ printf("%s hello thread\n", NowString().c_str()); });
	thread.join();
	printf("%s hello ptr %d \n", NowString().c_str(), sizeof(void*));
}
