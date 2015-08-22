#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <netinet/in.h>
#ifdef _XOPEN_SOURCE_EXTENDED
#include <arpa/inet.h>
#endif
#include <sys/socket.h>
#endif

#include <fcntl.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

// atoi
#include <stdlib.h>
// getopt
#include <unistd.h>
#include "WorkerThreads.h"
#include "global.h"

using namespace std;
//#include "WorkerThreads.h"

#define PORT	9999
#define DATA_BUFFER_SIZE 2048

struct Settings
{
	int num_threads;
};

struct Settings settings;

static struct event_base *main_base;

static int last_thread = -1;
WorkerThreads *workerThreads;

static redisContext* redis_context;

void thread_init(int nthreads)
{
	workerThreads = new WorkerThreads(nthreads);
	workerThreads->initiate();
}

void dispatch_conn_new(int sfd)
{
	CQ_ITEM *item = cqi_new();
	int tid = (last_thread + 1) % settings.num_threads;
	LIBEVENT_THREAD *thread = workerThreads->threads + tid;
	last_thread = tid;
	item->sfd = sfd;
	item->init_state = conn_read;
	item->event_flags = EV_READ | EV_PERSIST;
	item->transport = tcp_transport;

	cq_push(thread->new_conn_queue, item);
	int wc = write(thread->notify_send_fd, "t", 1);
}

void do_accept(evutil_socket_t listener, short event, void *arg)
{
	struct sockaddr_storage ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr*)&ss, &slen);
	if (fd < 0)
	{
		printf("Could not accept\n");
		return;
	}
	printf("establish one conn\n");
	dispatch_conn_new(fd); 
}

int main(int argc, char **argv)
{
	settings.num_threads = 10;
	int c;
	while (-1 != (c = getopt(argc, argv, "t:")))
	{
		switch (c)
		{
		case 't':
			settings.num_threads = atoi(optarg);
			break;
		}
	}

	struct sockaddr_in sin;
	evutil_socket_t listener;
	struct event *listener_event;
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif
	
	main_base = event_base_new();
	if (!main_base)
	{
		printf("Could not initialize libevent.\n");
		return 1;
	}
	
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	listener = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(listener);
#ifndef WIN32
	int one = 1;
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
#endif
	if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		printf("Counld bind socket\n");
		return 1;
	}

	if (listen(listener, 16) < 0)
	{
		printf("Counld listen\n");
		return 1;
	}

	listener_event = event_new(main_base, listener, EV_READ|EV_PERSIST, do_accept, (void*)main_base);
	event_add(listener_event, NULL);	
	conn_init();
	thread_init(settings.num_threads);

	event_base_dispatch(main_base);

	return 0;
}
