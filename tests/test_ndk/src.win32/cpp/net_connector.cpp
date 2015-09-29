#include "precompiled.h"
#include "net_connector.h"
#include "net_service_internal.h"

//	read event
void onRead( struct bufferevent * bev, void * ctx ) {
	
	// XE_NDC("onRead");

	CConnector * connector = (CConnector*)ctx;
	IConnector::Ptr ref = connector->shared_from_this();
	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "read once[connector(%s:%d)]", connector->remote_ip().c_str(), connector->remote_port());

	// char* buffer = &(*connector->GetRecvBuffer()->begin());
	// unsigned int size = connector->GetRecvBuffer()->size();
	char buffer[1024];
	unsigned int size = 1024;
	int read_size = 0;
	do {
		read_size = bufferevent_read(bev, buffer, size);
		if(read_size)
		{	
			connector->OnRecv(buffer, read_size);
			// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "read data(%d) [connector(%s:%d)]", read_size, connector->remote_ip().c_str(), connector->remote_port());
		}
	} while (read_size == size);
}

//	write event
void onWrite( struct bufferevent * bev, void * ctx ) {

	// XE_NDC("onWrite");
	CConnector * connector = (CConnector*)ctx;
	size_t size = evbuffer_get_length(bufferevent_get_output(bev));
	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "send data(%d) [connector(%s:%d)]", size, connector->remote_ip().c_str(), connector->remote_port());
	connector->OnSend(size);
	if(connector->shutdown() && size == 0) {
		::shutdown(connector->sock_id(), 1);
	}
}

//	error event
void onError( struct bufferevent * bev, short what, void * ctx ) {

	// XE_NDC("onError");
	CConnector * connector = (CConnector*)ctx;
	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "[what: %d connector(%s:%d)]", what, connector->remote_ip().c_str(), connector->remote_port());
	connector->ShutDownImmediately();
}

CConnector::CConnector( CNetService* net_service_impl ): net_service_impl_(net_service_impl) {
	// bufferev_ = 0;
	shutdown_ = false;
	data_ = 0;
	sink_ = 0;
}

CConnector::~CConnector( void ) {
	
}

bool CConnector::Init( int sock_id, IConnectorSink* sink, struct sockaddr* remote_addr ) {

	// XE_NDC("CConnector::Init");
	net_shutdown_listener_ = net_service_impl_->RegisterShutdownEventListener(boost::bind(&IConnector::Shutdown, shared_from_this() ));
	
	sock_id_ = sock_id;

	bufferev_ = boost::shared_ptr<bufferevent>( bufferevent_socket_new( net_service_impl_->ev_base(), sock_id, BEV_OPT_THREADSAFE), boost::bind(bufferevent_free, _1) );
	if(!bufferev_) {
		net_shutdown_listener_.Disconnect();
		// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_ERROR, "create bufferevent socket failed.");
		return false;
	}

	// ��������;
//	bufferevent_set_rate_limit(bufferev_.get(), net_service_impl_->ev_t_bucket_cfg());

	/* ��ȡ���ص�ַ�Ͷ˿� */
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
#ifdef DS_PLATFORM_WIN32
	getsockname(sock_id, (sockaddr*)&addr, &addrlen);
#else
	getsockname(sock_id, (sockaddr*)&addr, (socklen_t*)&addrlen);
#endif // DS_PLATFORM_WIN32

	local_ip_ = inet_ntoa(addr.sin_addr);
	local_port_ = ntohs(addr.sin_port);

	/* ��ȡԶ�̵�ַ�Ͷ˿� */
	if(remote_addr) {
		remote_ip_ = inet_ntoa(((struct sockaddr_in*)remote_addr)->sin_addr);
		remote_port_ = ntohs(((struct sockaddr_in*)remote_addr)->sin_port);
	}

	bufferev_weak_ = boost::weak_ptr<bufferevent>(bufferev_);

	set_sink(sink);

	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "init connector ok.[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
	return true;
}

bool CConnector::Send( const void * buffer, unsigned int size ) {
	
	// XE_NDC("CConnector::Send");
	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "send data(%d)[connector(%s:%d)]", size, remote_ip_.c_str(), remote_port_);
	if(shutdown_) {
		// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_ERROR, "connector is shutdowned yet[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
		return false;
	}

	boost::shared_ptr<bufferevent> bufferev = bufferev_weak_.lock();
	if(bufferev){
		bufferevent_write(bufferev.get(), buffer, size);
		return true;
	}

	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_ERROR, "bufferev is null[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
	return false;
}

void CConnector::Shutdown( void ) {

	// XE_NDC("CConnector::Shutdown");
	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "shutdown connector[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
	if(shutdown_) {
		// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_ERROR, "connector is shutdowned yet[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
		return;
	}

	shutdown_ = true;
	size_t size = 0;
	boost::shared_ptr<bufferevent> bufferev = bufferev_weak_.lock();
	if(bufferev){
		size = evbuffer_get_length(bufferevent_get_output(bufferev.get()));
	}

	if( size == 0) {
		::shutdown(sock_id_, 1);
	}

}

void CConnector::ShutDownImmediately( void ) {
	
	IConnector::Ptr ref = shared_from_this();
	// XE_NDC("CConnector::ShutDownImmediately");

	// XE_COMPONENT_LOG(// XE_COMPONENT_LOG_LEVEL_TRACE, "shutdown connector immediately[connector(%s:%d)]", remote_ip_.c_str(), remote_port_);
	shutdown_ = true;
	if(bufferev_)
	{
		bufferevent_setcb(bufferev_.get(), 0, 0, 0, 0);
		bufferevent_set_rate_limit(bufferev_.get(), 0);
		bufferev_.reset();
	}
	if(sink_) {
		sink_->OnDisconnect(shared_from_this());
		sink_->Release();
		sink_ = 0;
	}
	net_shutdown_listener_.Disconnect();
#ifdef DS_PLATFORM_WIN32
	closesocket(sock_id_);
#else
	close(sock_id_);
#endif // DS_PLATFORM_WIN32
}

void CConnector::OnSend( unsigned int size ) {
	
}

void CConnector::OnRecv( const void * buffer, unsigned int size ) {
	if(sink_) sink_->OnRecv( shared_from_this(), buffer, size);
}

void CConnector::set_sink( IConnectorSink* sink )
{
	sink_ = sink;

	if(sink_) sink_->OnConnect( shared_from_this() );
	bufferevent_setcb(bufferev_.get(), onRead, onWrite, onError, (void*)this);
	bufferevent_enable(bufferev_.get(), EV_READ | EV_WRITE | EV_PERSIST);
}

std::string* CConnector::GetRecvBuffer( void )
{
	return net_service_impl_->recv_buffer();
}




