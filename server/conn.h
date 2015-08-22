#ifndef __CONN__
#define __CONN__

#include "libevent_thread.h"
#include <stdlib.h>
#include <stdio.h>
#include "DataQueue.h"
#include "redishelp"

typedef struct
{
	int sfd;
	LIBEVENT_THREAD *thread;
	struct event read_event;
	struct event write_event;
	short ev_flags;
	bool bAuth;
	int nUserId;
	DataQueue read_dataqueue;
	DataQueue write_dataqueue;
	RedisHelp redisHelp;
} conn;

void conn_init();
void do_read(const int fd, const short which, void *arg);
void do_write(const int fd, const short which, void *arg);
conn *conn_from_freelist();
bool conn_add_to_freelist(conn *c);
void conn_free(conn *c);
conn* conn_new(const int sfd, enum conn_states init_state, const int event_flags, enum network_transport transport, struct event_base *base);

bool process_data(DataQueue *dq, conn *c);
void parse_package(const char *buff, size_t len, conn *c);
#endif
