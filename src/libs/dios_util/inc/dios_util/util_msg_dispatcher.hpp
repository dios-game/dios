#ifndef __DIOS_UTIL_MESSAGE_DISPATCHER_H__
#define __DIOS_UTIL_MESSAGE_DISPATCHER_H__

#include "dios_util_lib.h"
#include "util_byte_array.h"
#include "util_serializer.h"
#include <map>

#define DEFAULT_MSG_CODE 0
#define END_MSG_CODE 0

NS_DS_BEGIN
NS_UTIL_BEGIN  
/// \brief 消息派发器;
/// 
/// 详细说明：;
template<class T>
class CMessageDispatcher
{
public:
	typedef std::function<void(T*, const dios::util::CByteArray&)> HandleFunction;	
	virtual ~CMessageDispatcher() {}   
	/**	======================================*/
	void HandleMessage(T* session, const dios::util::CByteArray& logic_packet){	 
		int msg_code;
		CSerializer logic_packet_stream(logic_packet, logic_packet.size());
		logic_packet_stream>>msg_code;
		HandleFunction handle = _GetHandleFunction(msg_code);
		if(handle){
			handle(session, logic_packet_stream.data_last_read());
		}
		else {
			handle = handle_function_map_[DEFAULT_MSG_CODE];
			if(handle){
				handle(session, logic_packet);
			}
		}
	}
	
	void RegisterHandleFunction( int msg_code, HandleFunction msg_handle){	 
		handle_function_map_[msg_code] = msg_handle;
	}

	DS_SINGLETON(CMessageDispatcher<T>);

protected:			
	HandleFunction _GetHandleFunction(int msg_code){  
		typename std::map<int, HandleFunction>::iterator itor = handle_function_map_.find(msg_code);
		if(itor != handle_function_map_.end()){
			return itor->second;
		}
		return 0;
	}	  
	std::map<int, HandleFunction> handle_function_map_;
};

#define _DS_MESSAGE_DISPATCHER_CLASS_NAME(ExecuteClass)   XMessageHandle##ExecuteClass

#define _DS_MESSAGE_DISPATCHER_CLASS_INSTANCE_NAME(ExecuteClass)   XMessageHandleInstance##ExecuteClass

#define DS_MESSAGE_BEGIN(ExecuteClass, ModuleClass)                        \
class _DS_MESSAGE_DISPATCHER_CLASS_NAME(ModuleClass)                      \
{                                                   \
public:                                             \
	typedef dios::util::CMessageDispatcher<ExecuteClass> XMessageHandle;\
	_DS_MESSAGE_DISPATCHER_CLASS_NAME(ModuleClass)();                     \
} _DS_MESSAGE_DISPATCHER_CLASS_INSTANCE_NAME(ModuleClass);                \
_DS_MESSAGE_DISPATCHER_CLASS_NAME(ModuleClass)::_DS_MESSAGE_DISPATCHER_CLASS_NAME(ModuleClass)(){
#define DS_ON_MESSAGE(msg_code, msg_handle) XMessageHandle::GetInstancePtr()->RegisterHandleFunction( msg_code, &msg_handle );
#define DS_ON_DEFAULT(msg_handle) XMessageHandle::GetInstancePtr()->RegisterHandleFunction( DEFAULT_MSG_CODE, &msg_handle );
#define DS_MESSAGE_END() }

#define DS_MESSAGE_HANDLE3(ExecuteClass) dios::util::CMessageDispatcher<ExecuteClass>

NS_UTIL_END
NS_DS_END

#endif