#ifndef __LIBEVENT_THREAD__
#define __LIBEVENT_THREAD__
#include "cq.h"
#include <event.h>

struct LIBEVENT_THREAD
{
	pthread_t thread_id;
	struct event_base *base;
	struct event notify_event;

	int notify_receive_fd;
	int notify_send_fd;

	conn_queue *new_conn_queue;
};

static LIBEVENT_THREAD *threads = NULL;

struct LIBEVENT_DISPATCHER_THREAD
{
	pthread_t thread_id;
	struct event_base *base;
};
static LIBEVENT_DISPATCHER_THREAD dispatcher_thread;
#endif
