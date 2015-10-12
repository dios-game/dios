#ifndef ___PRECOMPILED_H_____
#define ___PRECOMPILED_H_____

//	common
#include <stdio.h>
#include <assert.h>

//	libevent;
#include "libevent/event2/util.h"
#include "libevent/event2/buffer.h"
#include "libevent/event2/bufferevent.h"
#include "libevent/event2/bufferevent_compat.h"
#include "libevent/event2/event.h"
#include "libevent/event2/listener.h"
#include "libevent/event2/thread.h"

#include "dios/platform.h"

#ifndef DS_PLATFORM_WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

//	pthread;
#ifdef DS_PLATFORM_WIN32
#include "pthread/pthread.h"
#endif

#include "component/com_network.h"

using namespace dios::com;

#endif
