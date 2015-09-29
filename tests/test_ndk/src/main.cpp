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
#include "net_service.h"	  
#include "net_service_internal.h"

void TestHttp(){

	CHttpServiceImpl http;
	std::string result;
	http.GetUrlData("http://www.baidu.com", result);
	printf("baidu %s\n", result.c_str());
}


class CServerConnectorSink :public IConnectorSink
{
public:
	virtual void OnConnect(const IConnector::Ptr&){ printf("server accepted\n");  }
	virtual void OnRecv(const IConnector::Ptr& connector, const void* buffer, unsigned int size){
		printf("server recv\n");

		connector->Send(buffer, size);
		printf("server send %s\n", buffer);
	}
	virtual void OnDisconnect(const IConnector::Ptr&){
		printf("server lost client \n");
	}

	virtual IConnectorSink* Clone() { return new CServerConnectorSink; }
	virtual void Release(){ delete this; }
};

class CClientConnectorSink :public IConnectorSink
{
public:
	virtual void OnConnect(const IConnector::Ptr&){ printf("client connected\n"); }
	virtual void OnRecv(const IConnector::Ptr& connector, const void* buffer, unsigned int size){
		printf("client recv\n");

		connector->Send(buffer, size);
		printf("client send\n");
	}
	virtual void OnDisconnect(const IConnector::Ptr&){
		printf("client disconnect\n");
	}

	virtual IConnectorSink* Clone() { return new CClientConnectorSink; }
	virtual void Release(){ delete this; }
};
void TestLibEvent(){
		
	CNetService* net_service = new CNetService;
	net_service->Initialize(1024);

	IServer::Ptr server = net_service->Listen("127.0.0.1", 8090, new CServerConnectorSink);
	IConnector::Ptr client = net_service->Connect("127.0.0.1", 8090, new CClientConnectorSink);
	client->Send("hello", 6);

	while (true){
		DS_SLEEP(1000);
	}

	client->Shutdown();
	server->Shutdown();
	net_service->Shutdown();
}

extern int TestMysql();
#else

void TestHttp(){   }

void TestLibEvent(){  }

int TestMysql() {}
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

	TestMysql();
}
