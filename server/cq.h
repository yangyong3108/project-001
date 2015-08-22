#ifndef __CQ__
#define __CQ__
#include <pthread.h>

#define ITEMS_PER_ALLOC 64

enum conn_states
{
	conn_listening,
	conn_new_cmd,
	conn_waiting,
	conn_read,
	conn_parse_cmd,
	conn_write,
	conn_nread,
	conn_swallow,
	conn_mwrite,
	conn_max_state,
};

enum network_transport
{
	local_transport,
	tcp_transport,
	udp_transport,
};

typedef struct conn_queue_item
{
	int sfd;
	enum conn_states init_state;
	int event_flags;
	enum network_transport transport;
	conn_queue_item *next;
} CQ_ITEM;

typedef struct conn_queue
{
	CQ_ITEM *head;
	CQ_ITEM *tail;
	pthread_mutex_t lock;
	pthread_cond_t cond;
} CQ;

CQ_ITEM *cq_pop(conn_queue *cq);
void cqi_free(CQ_ITEM *item);
void cq_init(conn_queue *cq);
CQ_ITEM *cqi_new(void);
void cq_push(conn_queue *cq, CQ_ITEM *item);

#endif
