#ifndef _DIOS_UTIL_BOOST_RESPONSER_H_
#define _DIOS_UTIL_BOOST_RESPONSER_H_

#include "dios_util_boost_lib.h"
#include "dios_util/util_byte_array.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

/*
 初始化;
 void RegisterResponseCallback( const std::function<void(const dios::util::CByteArray&)>& callback );
 void RegisterSendResponseDelegate( const std::function<bool(const dios::util::CByteArray&)>& delegate );

 处理请求;
 void HandleRequest(int request_order_id, const dios::util::CByteArray& logic_packet);

 处理确认;
 void HandleAck();

 发送响应;
 bool SendResponse( const void* buffer, ds_uint buffer_size, const std::function<void(const dios::util::CByteArray&)>& ack_callback );

 */
class DIOS_UTIL_BOOST_DECL CResponser
{
public:
	CResponser(); 
	virtual ~CResponser();

	void RegisterHandleRequestCallback( const std::function<void(const dios::util::CByteArray&)>& callback );
	void RegisterSendResponseDelegate( const std::function<bool(const dios::util::CByteArray&)>& delegate );

	void HandleRequest(const dios::util::CByteArray& logic_packet);
	void HandleAck();
	bool SendResponse( const void* buffer, ds_uint buffer_size, const std::function<void(const dios::util::CByteArray&)>& ack_callback );

	// protobuf type send;
	template<class MessageType>
	bool SendResponse( const MessageType& message, const std::function<void(const dios::util::CByteArray&)>& ack_callback=std::function<void(const dios::util::CByteArray&)>() ){
		std::string buffer;
		message.SerializeToString(&buffer);
		return SendResponse( buffer.data(), buffer.size(), ack_callback );
	}

protected:
	void _VerifyBuffer(dios::util::CByteArray** buffer, ds_uint need_size );

	int request_order_id_;
	dios::util::CByteArray* response_buffer_;
	int response_cache_buff_size_;

	std::function<void(const dios::util::CByteArray&)> ack_call_back_;
	std::function<void(const dios::util::CByteArray&)> handle_request_call_back_;
	std::function<bool(const dios::util::CByteArray&)> delegate_send_response_;
};
NS_UTIL_BOOST_END
NS_DS_END


#endif //_PLAYER_RESPONSE_MODULE_H_