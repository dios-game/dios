#ifndef DIOS_PROTOCOL_HEADER_H
#define DIOS_PROTOCOL_HEADER_H

#define COMMAND_DEFAULT 0
#define COMMAND_END 0xFFFFFFFF
typedef int MsgCode;

#define BEGIN_COMMAND_GROUP(marco_system, macro_from, macro_to) \
	COMMAND_##marco_system##_##macro_from##_##macro_to = ((marco_system << 24 & 0xFF000000) | (macro_from << 16 & 0x00FF0000) | ( macro_to << 8 & 0x0000FF00))

#define COMMAND_FROM_NET(command) ((command>>16) & 0xFF)

#define COMMAND_TO_NET(command) ((command>>8) & 0xFF)

enum DiosSystemEnum{

	DIOS_SYSTEM_INVALID = 0,
	DIOS_SYSTEM_REQUEST_RESPONSE_ACK = 251,
 	DIOS_SYSTEM_PING = 252,
	DIOS_SYSTEM_GROUP_SERVER = 253,
	DIOS_SYSTEM_ROUTE = 254,
	DIOS_SYSTEM_MAX = 255,
};

enum DiosNetTypeEnum{

	DIOS_NET_INVALID = 0,
	DIOS_NET_ANY = 251,
	DIOS_NET_GATE = 252,
	DIOS_NET_CLIENT = 253,
	DIOS_NET_MANAGER = 254, 
	DIOS_NET_MAX = 255,
};

enum DiosCommandEnum
{
	// ================ 华丽的分割线 ======================
	// DIOS_SYSTEM_GROUP_SERVER
	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_GROUP_SERVER, DIOS_NET_ANY, DIOS_NET_MANAGER ),
	REQUEST_GROUP_SERVER_CONNECT,
	REQUEST_GROUP_SERVER_RECONNECT,
	REQUEST_GOURP_SERVER_SYNC_TIME,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_GROUP_SERVER, DIOS_NET_MANAGER, DIOS_NET_ANY ),	
	NOTIFY_GOURP_SERVER_ID,
	NOTIFY_GOURP_SERVER_DEPEND,
	NOTIFY_GOURP_SERVER_CONNECT_FINISH,
	RESPONSE_GOURP_SERVER_SYNC_TIME,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_GROUP_SERVER, DIOS_NET_ANY, DIOS_NET_ANY ),
	REQUEST_REQUEST_GROUP_SERVER_CONNECT_TO_GROUP_SERVER,
	REDIRECT_PACKET_TO_PLAYER,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_ROUTE, DIOS_NET_ANY, DIOS_NET_GATE),
	REQUEST_ADD_ROUTER,
	REQUEST_SHUTDOWN_PLAYER,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_ROUTE, DIOS_NET_GATE, DIOS_NET_ANY),
	NOTIFY_ROUTER_ADDED,
	NOTIFY_ROUTER_DELETED,
	NOTIFY_PLAYER_SESSION_INFO,
	NOTIFY_PLAYER_SESSION_STATE_ONLINE,
	NOTIFY_PLAYER_SESSION_STATE_OFFLINE,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_ROUTE, DIOS_NET_CLIENT, DIOS_NET_GATE),
	CLIENT_CONNECT,
	CLIENT_RECONNECT,
	REQUEST_CLIENT_SYNC_TIME,

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_ROUTE, DIOS_NET_GATE, DIOS_NET_CLIENT),
	NOTIFY_CLIENT_TOKEN,
	NOTIFY_CLIENT_RECONNECTED,
	NOTIFY_CLIENT_RECONNECT_FAILED,
	RESPONSE_CLIENT_SYNC_TIME,
	NOTIFY_KICK_BY_ROUTER_IS_NOT_EXISTED,

	// ================ 华丽的分割线 ====================== 
	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_REQUEST_RESPONSE_ACK, DIOS_NET_ANY, DIOS_NET_CLIENT),
	RESPONSE_CLIENT_REQUEST,

	// ================ 华丽的分割线 ======================
	// DIOS_SYSTEM_PING
	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_PING, DIOS_NET_CLIENT, DIOS_NET_ANY),
	CLIENT_PING,	// PING

	BEGIN_COMMAND_GROUP( DIOS_SYSTEM_PING, DIOS_NET_ANY, DIOS_NET_CLIENT),
	SERVER_PONG,
};


#endif // SERVER_FRAMEWORK_PROTOCOL_HEADER_H
