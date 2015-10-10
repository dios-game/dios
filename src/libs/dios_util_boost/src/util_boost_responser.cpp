#include "precompiled.h"
#include "util_boost_responser.h"
#include "protocol/dios_protocol_header.h"
#include "dios_util/util_serializer.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

CResponser::CResponser() :response_buffer_(NULL)
{
	response_cache_buff_size_ = 0;
	request_order_id_ = 0;
}

CResponser::~CResponser()
{
	DS_SAFE_DELETE(response_buffer_);
}

void CResponser::RegisterHandleRequestCallback( const std::function<void(const dios::util::CByteArray&)>& callback )
{
	handle_request_call_back_ = callback;
}

void CResponser::HandleRequest( const dios::util::CByteArray& logic_packet )
{
	int request_order_id; 
	dios::util::CSerializer logic_packet_stream(logic_packet, logic_packet.size());
	logic_packet_stream>>request_order_id;
	if(request_order_id_==request_order_id){
		if(delegate_send_response_ && response_buffer_){
			dios::util::CByteArray buffer_temp(*response_buffer_, 0, response_cache_buff_size_);
			delegate_send_response_(buffer_temp);
		}
	}
	else{
		request_order_id_ = request_order_id;
		if(handle_request_call_back_){
			handle_request_call_back_(logic_packet_stream.data_last_read());
		}
	}
}

bool CResponser::SendResponse( const void* buffer, ds_uint buffer_size, const std::function<void(const dios::util::CByteArray&)>& ack_callback )
{
	bool rtn = false;
	do 
	{
		response_cache_buff_size_ = buffer_size+sizeof(int)+sizeof(int)+sizeof(request_order_id_);
		ack_call_back_ = ack_callback;

		// ####### send request package
		_VerifyBuffer(&response_buffer_, response_cache_buff_size_);

		dios::util::CSerializer request_packet_stream( *response_buffer_ );
		request_packet_stream.WriteInt(RESPONSE_CLIENT_REQUEST);
		request_packet_stream<<request_order_id_;
		request_packet_stream.WriteInt(ack_callback?1:0);
		request_packet_stream.Write(buffer, buffer_size);
		DS_BREAK_IF(!delegate_send_response_);
		rtn = delegate_send_response_(request_packet_stream.data());
	} while (0);

	return rtn;
}

void CResponser::HandleAck()
{
	int header_size = sizeof(int)+sizeof(int)+sizeof(request_order_id_);
	if(ack_call_back_) ack_call_back_(dios::util::CByteArray(*response_buffer_, header_size, response_cache_buff_size_-header_size));
}

void CResponser::_VerifyBuffer( dios::util::CByteArray** buffer, ds_uint need_size )
{
	if(*buffer){
		if(need_size <= (*buffer)->size()){
			return;
		}
		DS_SAFE_DELETE(*buffer);
	}

	char* buff = (char*)malloc(need_size);
	*buffer = new dios::util::CByteArray(buff, need_size);
}

void CResponser::RegisterSendResponseDelegate( const std::function<bool(const dios::util::CByteArray&)>& delegate )
{
	delegate_send_response_ = delegate;
}

NS_UTIL_BOOST_END
NS_DS_END


