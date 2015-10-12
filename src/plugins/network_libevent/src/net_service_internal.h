#ifndef NET_ENGINE_IMPL_H
#define NET_ENGINE_IMPL_H

class CNetService : public dios::com::INetworkContext
{
public:
	~CNetService(void);
	CNetService(void);

	virtual bool Initialize( unsigned int recv_size );	
	virtual bool Shutdown( void );	
	virtual dios::com::IServer::Ptr Listen( const char * local_ip, int local_port, IConnectorSink* sink );
	virtual IConnector::Ptr	Connect( const char * remote_ip, int remote_port, IConnectorSink* sink );

	void NullConnect( const char * remote_ip, int remote_port);

	//	get event_base;
	inline event_base * ev_base(void) { return ev_base_; }

	//	get event;
	inline event * ev(void) { return ev_; }

	// get ev_token_bucket_cfg;
	inline ev_token_bucket_cfg * ev_t_bucket_cfg(void) { return ev_t_bucket_cfg_; }

	dios::util::CEventListener RegisterShutdownEventListener(boost::function<void()> func);

	//	recv size
	std::string* recv_buffer(void);
private:
	dios::util::CEvent2<void()> net_shutdown_event_;

	//	libevent core;
	event_config * ev_config_;
	event_base * ev_base_;
	event * ev_;
	ev_token_bucket_cfg * ev_t_bucket_cfg_;

	//	loop thread;
	pthread_t loop_thread_;
	bool is_running_;

	std::mutex running_mutex_;

	// custom;
	dios::util_boost::CTlsBuffer tls_recv_buffer_;
};

#endif