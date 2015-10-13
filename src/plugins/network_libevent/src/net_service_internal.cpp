#include "precompiled.h"
#include "net_service_internal.h"
#include "net_connector.h"
#include "net_server.h"

#include "dios_util/util_memory.hpp"

//	default event callback function
void defaultEventFunc(evutil_socket_t, short, void * ptr) {
	timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	CNetService* net_service = (CNetService*)ptr;
	event_add(net_service->ev(), &tv);
}

//	loop thread
void * loopThreadStartFunc( void * ptr ) {
	CNetService* net_service = (CNetService*)ptr;
	event_base_dispatch(net_service->ev_base());
	return 0;
}

//	net engine
CNetService::CNetService( void ) {
	ev_config_ = 0;
	ev_base_ = 0;
	ev_ = 0;
	is_running_ = false;
}

CNetService::~CNetService( void ) {
	Shutdown();
}

bool CNetService::Initialize( unsigned int recv_size ) {

	std::unique_lock<std::mutex> lock(running_mutex_);
	if(is_running_) 
	{
		sLogError("net service is initialized");
		return false;
	}

	if(recv_size == 0) {
		sLogError("recv_size cannot be 0" );
		return false;
	}

	tls_recv_buffer_.set_default_size(recv_size);

#ifdef WIN32
	//	wsa init
	WSAData wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		sLogError("net service initialize WSAStartup failed.");
		return false;
	}

	sLogTrace("wsastartup ok.");

	//	about thread and lock
	evthread_use_windows_threads();
	sLogTrace("evthread_set ok.");

	//	get count of processors
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	sLogTrace("getsysteminfo ok. numberofprocessors: %u.", sysInfo.dwNumberOfProcessors);

	//	event config
	ev_config_ = event_config_new();
	event_config_set_flag(ev_config_, EVENT_BASE_FLAG_STARTUP_IOCP);
	event_config_set_num_cpus_hint(ev_config_, sysInfo.dwNumberOfProcessors);
	sLogTrace("event_config_set ok.");
#else
	//	about thread and lock
	evthread_use_pthreads();

	//	event config
	ev_config_ = event_config_new();
	event_config_set_flag(ev_config_, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);
	sLogTrace("event_config_set ok.");
#endif

	//	event base
	ev_base_ = event_base_new_with_config(ev_config_);
	sLogTrace("event_base_new ok.");

	// tv
	timeval tv;

	// ev token bucket cfg
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	ev_t_bucket_cfg_ = ev_token_bucket_cfg_new(EV_RATE_LIMIT_MAX, EV_RATE_LIMIT_MAX, 1024, 1024, &tv);
	sLogTrace("ev_token_bucket_cfg_new ok.");

	//	set an event
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	ev_ = evtimer_new(ev_base_, defaultEventFunc, this);
	event_add(ev_, &tv);
	sLogTrace("event_add timer ok.");
	
	// run loop callback
	pthread_create(&loop_thread_, 0, loopThreadStartFunc, this);
	sLogTrace("main thread create ok.");

	//	start
	is_running_ = true;
	sLogInfo("Initialize Finish.");
	return true;
}

bool CNetService::Shutdown( void ) {
	
	// set running flag   
	std::unique_lock<std::mutex> lock(running_mutex_);
	if(!is_running_) 
	{
		sLogError("net service is shutdowned.");
		return false;
	}
	is_running_ = false;	

	// wait for all net_shut_down
	net_shutdown_event_();
	sLogTrace("shutdown_signal_.num_slots: %d.", net_shutdown_event_.NumListeners());
	while( net_shutdown_event_.NumListeners() ){
		DS_SLEEP(2000);
		sLogTrace("shutdown_signal_.num_slots: %d.", net_shutdown_event_.NumListeners());
	}

	// leave loop;
	event_base_loopexit(ev_base_, 0);
	pthread_join(loop_thread_, 0);
	sLogTrace("waiting for thread exit.");

	// free libevent object;
	event_free(ev_);
	event_base_free(ev_base_);
	ev_token_bucket_cfg_free(ev_t_bucket_cfg_);
	event_config_free(ev_config_);
	sLogTrace("free event environment ok.");
	sLogInfo("Shutdown Finish.");
	return true;
}

IServer::Ptr CNetService::Listen( const char * local_ip, int local_port, IConnectorSink* sink ) {
	
	std::unique_lock<std::mutex> lock(running_mutex_);
	if(!is_running_) 
	{
		sLogError("net service is shutdowned.");
		return IServer::Ptr();
	}

	CServer::Ptr ptr(new CServer(this));
	if (ptr->Init(local_ip, local_port, sink)) {
		return ptr;
	}
	return IServer::Ptr();
}

IConnector::Ptr	CNetService::Connect( const char * remote_ip, int remote_port, IConnectorSink* sink ){

	std::unique_lock<std::mutex> lock(running_mutex_);
	if(!is_running_){
		sLogError("net service is shutdowned.");
		return IConnector::Ptr();
	}

	int connect_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(connect_fd <= 0) {
		sLogError("request socket failed.(connector(%s:%d)", remote_ip, remote_port);
		return IConnector::Ptr();
	}

	//	config address
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(remote_ip);
	sin.sin_port = htons(remote_port);

	//	create connector
	int result = ::connect(connect_fd, (sockaddr*)&sin, sizeof(sin));
	if(result == -1) {
		sLogError("connect failed. error code: %d.(connector(%s:%d)", result, remote_ip, remote_port);
		return IConnector::Ptr();
	}

	CConnector::Ptr ptr(new CConnector(this));
	if(ptr->Init(connect_fd, sink, (struct sockaddr*)&sin))
		return ptr;

	return CConnector::Ptr();
}


dios::util::CEventListener CNetService::RegisterShutdownEventListener(std::function<void()> func)
{
	return net_shutdown_event_.Connect( func );
}

std::string* CNetService::recv_buffer( void )
{
	return tls_recv_buffer_.GetBuffer();
}

void CNetService::NullConnect( const char * remote_ip, int remote_port )
{
	int connect_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(connect_fd <= 0) {
		sLogError("request socket failed.(connector(%s:%d)", remote_ip, remote_port);
		return;
	}

	//	config address
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(remote_ip);
	sin.sin_port = htons(remote_port);

	//	create connector
	int result = ::connect(connect_fd, (sockaddr*)&sin, sizeof(sin));
	if(result == -1) {
		sLogError("connect failed. error code: %d.(connector(%s:%d)", result, remote_ip, remote_port);
		return;
	}

	CConnector::Ptr connector(new CConnector(this));
	if(connector->Init(connect_fd, 0, (struct sockaddr*)&sin)){
		connector->Shutdown();
	}
}




PLUGIN_EXPORT(network_libevent){  
	PLUGIN_EXPORT_COM("network_libevent", CNetService)
}
