#ifndef _DIOS_UTIL_BOOST_REQUESTER_H_
#define _DIOS_UTIL_BOOST_REQUESTER_H_


#include "dios_util_boost_lib.h"
#include <map>

#include "dios_util/util_byte_array.h"
#include "dios_util/util_event_set.hpp"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 初始化;
 void ResgisterSendReqestDelegate( const std::function<bool( const void* , ds_uint )>& delegate_send_request );
 void ResgisterSendAckDelegate( const std::function<bool( const void* , ds_uint )>& delegate_send_ack );
 void ResgisterMsgCode( int dest_server_type, int request_msg_code, int ack_msg_code );
 template<typename T> void RegisterRequestExceptionEvent( const T& cb); T=void()
 template<typename T> void RegisterRequestWaitingEvent( const T& cb); T=void()

 发送请求;
 bool SendRequest( int msg_code, const void* buffer, ds_uint buffer_size, const std::function<void(const void*, ds_uint)>& response_callback );

 更新确认;
 void Update( float delta );

 处理响应;
 void HandleResponse( const dios::util::CByteArray& buffer );

 */

class DIOS_UTIL_BOOST_DECL CRequester{

public:

	enum RequestState {

		REQUEST_IDLE,
		REQUEST_REQUESTING,
		REQUEST_ACKING,
	};

	CRequester();
	~CRequester();

	bool Retry();

	void Done( bool exception_error );

	bool SendRequest(int msg_code, const void* buffer, ds_uint buffer_size, const std::function<void(const void*, ds_uint)>& response_callback);

	// protobuf type send;
	template<class MessageType>
	bool SendRequest(int msg_code, const MessageType& message, const std::function<void(const void*, ds_uint)>& response_callback){
		std::string buffer;
		message.SerializeToString(&buffer);
		return SendRequest( msg_code, buffer.data(), buffer.size(), response_callback );
	}

	void HandleResponse( const dios::util::CByteArray& buffer );

	void Update( float delta );

	void ResgisterSendReqestDelegate(const std::function<bool(const void*, ds_uint)>& delegate_send_request);
	void ResgisterSendAckDelegate(const std::function<bool(const void*, ds_uint)>& delegate_send_ack);
	void ResgisterMsgCode( int dest_server_type, int request_msg_code, int ack_msg_code );

	template<typename T>
	void RegisterRequestDoneEvent( const T& cb){
		event_request_done_ += cb;
	}

	template<typename T>
	void UnregisterRequestDoneEvent( const T& cb){
		event_request_done_ -= cb;
	}

	template<typename T>
	void RegisterRequestWaitingEvent( const T& cb){
		event_request_waiting_ += cb;
	}

	template<typename T>
	void UnregisterRequestWaitingEvent( const T& cb){
		event_request_waiting_ -= cb;
	}

	inline RequestState state(void) { return state_; }

	DS_PROPERTY(ds_int32, ack_time_out);
	DS_PROPERTY(ds_int32, request_time_out);

protected:
	int _GetRequestMessageCode(int dest_server_type);
	int _GetAckMessageCode(int dest_server_type);
	bool _SendRequest( const void* buffer, ds_uint buffer_size);
	bool _SendAck( const void* buffer, ds_uint buffer_size);

	void _UpdateRequest();
	void _UpdateAck();
	void _VerifyBuffer(dios::util::CByteArray** buffer, ds_uint need_size );
	void _Process( const dios::util::CByteArray& buffer );
	

	dios::util::CByteArray* request_buffer_;
	dios::util::CByteArray* response_buffer_;
	dios::util::CByteArray* ack_buffer_;
	RequestState state_;
	int request_order_id_;
	int dest_server_type_;
	int request_cache_buff_size_;
	int response_cache_buff_size_;

	ds_uint32 ack_time_out_tick_;
	ds_uint32 request_time_out_tick_;

	std::function<void(const void*, ds_uint)> response_call_back_;
	dios::util::CEvent<void(bool)> event_request_done_;
	dios::util::CEvent<void()> event_request_waiting_;

	// 发送请求托管,一般为异步发送;
	std::function<bool( const void* , ds_uint )> delegate_send_request_;
	// 发送请求托管,必须为同步发送;
	std::function<bool( const void* , ds_uint )> delegate_send_ack_;

	std::map<int, int> map_request_msg_code_;
	std::map<int, int> map_ack_msg_code_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif
