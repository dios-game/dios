#ifndef _____NET_SERVICE_H_________
#define _____NET_SERVICE_H_________

#include "dios/platform.h"
#include "dios_com/dios_com.h"

namespace dios{

	namespace com{

		class IConnectorSink;

		/*
		*	��INetworkContext��������
		*/
		class IConnector : public std::enable_shared_from_this<IConnector>
		{
		public:
			typedef std::shared_ptr<IConnector> Ptr;
			typedef std::weak_ptr<IConnector> WeakPtr;

			virtual ~IConnector() {}

			// ��������;
			virtual bool Send(const void * buffer, unsigned int size) = 0;
			virtual void Shutdown(void) = 0;

			/*
			*	����������Ϣ;
			*/
			virtual std::string local_ip() = 0;
			virtual int local_port() = 0;
			virtual std::string remote_ip() = 0;
			virtual int remote_port() = 0;
		};

		/*
		*	��INetworkContext��������
		*/
		class IServer : public std::enable_shared_from_this<IServer>
		{
		public:
			typedef std::shared_ptr<IServer> Ptr;

			virtual ~IServer() {}

			/*
			*	�رշ�����;
			*/
			virtual void Shutdown(void) = 0;

			/*
			*	������Ϣ;
			*/
			virtual std::string local_ip() = 0;
			virtual int local_port() = 0;
		};

		class INetworkContext : public ICom
		{
		public:
			typedef std::shared_ptr<INetworkContext> Ptr;
			typedef std::weak_ptr<INetworkContext> WeakPtr;
			virtual ~INetworkContext(void)	{}

			virtual bool Initialize(unsigned int recv_size) = 0;
			virtual bool Shutdown(void) = 0;

			/*
			*	����˼����������ӽ���ʱ����AcceptCallback
			*/
			virtual IServer::Ptr Listen(const char * local_ip, int local_port, IConnectorSink* sink) = 0;

			/*
			*	�ͻ������ӣ����ӳɹ�ʱ����AcceptCallback
			*/
			virtual IConnector::Ptr	Connect(const char * remote_ip, int remote_port, IConnectorSink* sink) = 0;
		};

		// �¼�������;
		class IConnectorSink
		{
		public:
			virtual void OnConnect(const IConnector::Ptr&) = 0;
			virtual void OnRecv(const IConnector::Ptr&, const void* buffer, unsigned int size) = 0;
			virtual void OnDisconnect(const IConnector::Ptr&) = 0;

			virtual IConnectorSink* Clone() = 0;
			virtual void Release() = 0;
		};
	}
}


#endif
