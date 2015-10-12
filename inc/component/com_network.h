#ifndef __COM_NETWORK_H___
#define __COM_NETWORK_H___

#include "dios/platform.h"

NS_DS_BEGIN 
namespace com{
	class IConnectorSink;

	struct EndPoint{
		std::string ip;
		ds_uint32 port;
	};

	/*
	 *	由INetWorkContext创建产生
	 */
	class IConnector : public std::enable_shared_from_this<IConnector>
	{
	public:
		typedef std::shared_ptr<IConnector> Ptr;
		typedef std::weak_ptr<IConnector> WeakPtr;

		virtual ~IConnector() {}

		// 链接基本操作;
		virtual bool Connect(const string& remote_ip, ds_uint32 remote_port, IConnectorSink* sink)
			virtual bool Send(const void * buffer, unsigned int size) = 0;
		virtual void Shutdown(void) = 0;

		// 基本网络信息;
		virtual const EndPoint& local() = 0;
		virtual const EndPoint& remote() = 0;
		virtual IConnectorSink* sink() = 0;
	};

	// 事件接收器;
	class IConnectorSink
	{
	public:
		virtual void OnConnect(const IConnector::Ptr&) = 0;
		virtual void OnRecv(const IConnector::Ptr&, void* buffer, ds_uint32 size) = 0;
		virtual void OnDisconnect(const IConnector::Ptr&) = 0;

		virtual IConnectorSink* Clone() = 0;
		virtual void Release() = 0;
	};

	class IAcceptor : public std::enable_shared_from_this<IServer>
	{
	public:
		typedef std::shared_ptr<IServer> Ptr;

		virtual ~IAcceptor() {}

		// 监听器基本操作;
		virtual void Listen(const string& local_ip, ds_uint32 local_port, IConnectorSink* sink)
			virtual void Shutdown(void) = 0;
		virtual const EndPoint& local() = 0;
	};

	class INetworkContext : public ICom
	{
	public:
		typedef std::shared_ptr<INetworkContext> Ptr;
		typedef std::weak_ptr<INetworkContext> WeakPtr;

		virtual ~INetworkContext(void)	{}

		virtual bool Initialize(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual IConnector::Ptr MakeConnector() = 0;
		virtual IAcceptor::Ptr MakeAcceptor() = 0;

		// 基本参数设置;
		virtual void SetUnitRecvSize(ds_uint32 unit_recv_size);
	};
}

NS_DS_END

#endif