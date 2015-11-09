#include "precompiled.h"
#include <stdio.h>

#include "component/com_network.h"	   
#include "component/com_log.h"

#include "util_log.h"

class CServerConnector : public dios::com::IConnectorSink{

public:
	virtual void OnConnect(const dios::com::IConnector::Ptr& connector){
		sLogInfo("server connector connect");
	}
	virtual void OnRecv(const dios::com::IConnector::Ptr& connector, const void* buffer, unsigned int size){
		sLogInfo("server recv: %s", (char*)buffer);
		connector->Send(buffer, size);
	}
	virtual void OnDisconnect(const dios::com::IConnector::Ptr& connector){
		sLogInfo("server connector disconnnect");
	}

	virtual IConnectorSink* Clone(){
		return new CServerConnector;
	}
	virtual void Release(){
		delete this;
	}
};

class CClientConnector : public dios::com::IConnectorSink{

public:
	virtual void OnConnect(const dios::com::IConnector::Ptr& connector){
		sLogInfo("client connector connect");
	}
	virtual void OnRecv(const dios::com::IConnector::Ptr& connector, const void* buffer, unsigned int size){
		sLogInfo("client recv: %s", (char*)buffer);
		// connector->Send(buffer, size);
	}
	virtual void OnDisconnect(const dios::com::IConnector::Ptr& connector){
		sLogInfo("client connector disconnect");
	}

	virtual IConnectorSink* Clone(){
		return new CClientConnector;
	}
	virtual void Release(){
		delete this;
	}
};


void InitLog(){
	sComContext->LoadPlugin("log_log4cplus");
	dios::com::ILogContext::Ptr log_context = sComContext->CreateCom<dios::com::ILogContext>("log_log4cplus"); 
	if (log_context){
		log_context->Initialize("log.properties");
		dios::com::ILog::Ptr log = log_context->CreateLog("root");
		sLog->SetLogCallBack([log](int level, const std::string& message){
			switch (level)
			{
			case dios::util::CLog::LOG_LEVEL_TRACE:
				log->Trace("%s", message.c_str());
				break;
			case dios::util::CLog::LOG_LEVEL_DEBUG:
				log->Debug("%s", message.c_str());
				break;
			case dios::util::CLog::LOG_LEVEL_INFO:
				log->Info("%s", message.c_str());
				break;
			case dios::util::CLog::LOG_LEVEL_WARN:
				log->Warn("%s", message.c_str());
				break;
			case dios::util::CLog::LOG_LEVEL_ERROR:
				log->Error("%s", message.c_str());
				break;
			case dios::util::CLog::LOG_LEVEL_FATAL:
				log->Fatal("%s", message.c_str());
				break;
			default:
				break;
			}
		});
	}
}

void TestNetwork(){
	InitLog();

	sLogInfo("TestNetwork start");
	sComContext->LoadPlugin("network_libevent");

	dios::com::INetworkContext::Ptr context = sComContext->CreateCom<dios::com::INetworkContext>("network_libevent");

	if (context){
		context->Initialize(8096);
		auto server = context->Listen("127.0.0.1", 8090, new CServerConnector());
		if (server){

			auto client = context->Connect("127.0.0.1", 8090, new CClientConnector());
			client->Send("hello world", 12);
		}
	}
	getchar();
}
