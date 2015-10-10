#include "precompiled.h"
#include "util_boost_requester.h"
#include "protocol/dios_protocol_header.h"
#include "dios_util/util_serializer.h"
#include "dios_util/util_timer.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

CRequester::CRequester()
{
	request_buffer_ = 0;
	response_buffer_ = 0;
	ack_buffer_ = 0;

	_VerifyBuffer(&request_buffer_, 1024);
	_VerifyBuffer(&response_buffer_, 1024);
	_VerifyBuffer(&ack_buffer_, 64);

	state_ = REQUEST_IDLE;
	ack_time_out_tick_ = 0;
	ack_time_out_ = 6000;
	request_time_out_tick_ = 0;
	request_time_out_ = 6000;
	dest_server_type_ = 0;
	response_cache_buff_size_ = 0;
	request_cache_buff_size_ = 0;
	request_order_id_ = 1;
}

CRequester::~CRequester()
{
	DS_SAFE_DELETE(response_buffer_);
	DS_SAFE_DELETE(request_buffer_);
}

bool CRequester::Retry()
{
	bool rtn = false;
	do 
	{
		DS_BREAK_IF(!request_buffer_);
		DS_BREAK_IF(state_!=REQUEST_IDLE);
		DS_BREAK_IF(!_SendRequest(request_buffer_->ptr(), request_cache_buff_size_));

		// ####### send request ok
		request_time_out_tick_ = dios::util::CTimer::GetMilliSecond()+request_time_out_;
		state_ = REQUEST_REQUESTING;
		rtn = true;
		event_request_waiting_();
	} while (0);
	return rtn;
}

bool CRequester::SendRequest( int msg_code, const void* buffer, ds_uint buffer_size, const std::function<void(const void*, ds_uint)>& response_callback )
{
	bool rtn = false;
	do 
	{
		DS_BREAK_IF(state_!=REQUEST_IDLE);
		dest_server_type_ = COMMAND_TO_NET(msg_code);

		// ####### send request package
		int request_msg_code = _GetRequestMessageCode(dest_server_type_);
		int request_header_size = sizeof(request_msg_code) + sizeof(request_order_id_) + sizeof(msg_code);
		request_cache_buff_size_ = buffer_size+request_header_size;
		_VerifyBuffer(&request_buffer_, request_cache_buff_size_);

		dios::util::CSerializer request_packet_stream(*request_buffer_);
		request_packet_stream<<request_msg_code;
		request_packet_stream<<request_order_id_;
		request_packet_stream<<msg_code;
		request_packet_stream.Write(buffer, buffer_size);

		dios::util::CByteArray buffer_temp = request_packet_stream.data();
		DS_BREAK_IF(!_SendRequest(buffer_temp.ptr(), buffer_temp.size()));

		// ####### send request ok
		response_call_back_ = response_callback;
		request_time_out_tick_ = dios::util::CTimer::GetMilliSecond()+request_time_out_;
		state_ = REQUEST_REQUESTING;
		rtn = true;
		event_request_waiting_();
	} while (0);

	return rtn;
}

void CRequester::HandleResponse( const dios::util::CByteArray& buffer )
{
	do 
	{
		DS_BREAK_IF( state_ != REQUEST_REQUESTING );

		// ####### unpack response ok;
		int request_order_id;
		int need_acking;
		dios::util::CSerializer response_packet_stream( buffer, buffer.size() );
		response_packet_stream>>request_order_id;
		response_packet_stream>>need_acking;

		// ###### it is not current request then ignore;
		DS_BREAK_IF( request_order_id!=request_order_id_ );

		// ###### if ack need then send, or process;
		dios::util::CByteArray buffer_temp = response_packet_stream.data_last_read();
		if(need_acking){
			_VerifyBuffer(&response_buffer_, buffer_temp.size());

			memcpy(response_buffer_->ptr(), buffer_temp.ptr(), buffer_temp.size());
			response_cache_buff_size_ = buffer_temp.size();
			ack_time_out_tick_ = dios::util::CTimer::GetMilliSecond()+ack_time_out_;
			state_ = REQUEST_ACKING;
		}
		else{
			_Process(buffer_temp);
		}
	} while (0);
}

void CRequester::Done( bool exception_error )
{
	if(REQUEST_IDLE!=state_){
		state_ = REQUEST_IDLE;
		event_request_done_(!exception_error);
	}
}

void CRequester::Update(  float delta  )
{
	_UpdateRequest();
	_UpdateAck();
}


void CRequester::_UpdateRequest()
{
	do 
	{
		DS_BREAK_IF( state_ != REQUEST_REQUESTING );

		ds_int32 delta = dios::util::CTimer::GetMilliSecond() - request_time_out_tick_;
		if(delta > 0){
			Done(true);
			return;
		}
	} while (0);
}

void CRequester::_UpdateAck()
{
	do 
	{
		DS_BREAK_IF( state_ != REQUEST_ACKING );

		ds_int32 delta = dios::util::CTimer::GetMilliSecond() - ack_time_out_tick_;
		if(delta > 0){
			Done(true);
			return;
		}

		// ##### send ack;
		int ack_msg_code = _GetAckMessageCode(dest_server_type_);
		_VerifyBuffer(&ack_buffer_, sizeof(ack_msg_code)+sizeof(request_order_id_));
		dios::util::CSerializer ack_packet_stream(*ack_buffer_);
		ack_packet_stream<<ack_msg_code;
		ack_packet_stream<<request_order_id_;
		dios::util::CByteArray buffer_temp = ack_packet_stream.data();
		DS_BREAK_IF(!_SendAck(buffer_temp.ptr(), buffer_temp.size()));

		// ##### process;
		_Process(dios::util::CByteArray(response_buffer_->ptr(), response_cache_buff_size_));
	} while (0);
}

void CRequester::_VerifyBuffer( dios::util::CByteArray** buffer, ds_uint need_size )
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

void CRequester::_Process(  const dios::util::CByteArray& buffer )
{
	++ request_order_id_;

	Done(false);

	if(response_call_back_){
		response_call_back_(buffer.ptr(), buffer.size());
	}
}

void CRequester::ResgisterSendReqestDelegate( const std::function<bool( const void* , ds_uint )>& delegate_send_request )
{
	delegate_send_request_ = delegate_send_request;
}

void CRequester::ResgisterSendAckDelegate( const std::function<bool( const void* , ds_uint )>& delegate_send_ack )
{
	delegate_send_ack_ = delegate_send_ack;
}

void CRequester::ResgisterMsgCode( int dest_server_type, int request_msg_code, int ack_msg_code )
{
	map_request_msg_code_[dest_server_type] = request_msg_code;
	map_ack_msg_code_[dest_server_type] = ack_msg_code;
}

int CRequester::_GetRequestMessageCode( int dest_server_type )
{
	return map_request_msg_code_[dest_server_type];
}

int CRequester::_GetAckMessageCode( int dest_server_type )
{
	return map_ack_msg_code_[dest_server_type];
}

bool CRequester::_SendRequest( const void* buffer, ds_uint buffer_size )
{
	if(delegate_send_request_){
		return delegate_send_request_(buffer, buffer_size);
	}
	return false;
}

bool CRequester::_SendAck( const void* buffer, ds_uint buffer_size )
{
	if(delegate_send_ack_){
		return delegate_send_ack_(buffer, buffer_size);
	}
	return false;
}



NS_UTIL_BOOST_END
NS_DS_END







