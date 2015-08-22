#include "WorkerThreads.h"
#include <stdio.h>

void WorkerThreads::initiate()
{
	int i;
	threads = (LIBEVENT_THREAD*)calloc(nthreads, sizeof(LIBEVENT_THREAD));
	if (!threads)
	{
		printf("can't allocate thread");
		exit(1);
	}
	for (i = 0; i < nthreads; i++)
	{
		int fds[2];
		if (-1 == pipe(fds))
		{
			printf("can't create notify pipe");
			exit(1);
		}
		threads[i].notify_receive_fd = fds[0];
		threads[i].notify_send_fd = fds[1];
		setup_event_thread(&threads[i]);
	}
	for (i = 0; i < nthreads; i++)
	{
		create_worker(worker_libevent, &threads[i]);
	}
	pthread_mutex_lock(&init_lock);
	while (init_count < nthreads)
	{
		pthread_cond_wait(&init_cond, &init_lock);
	}
	pthread_mutex_unlock(&init_lock);

	printf("finish\n");
}

void WorkerThreads::setup_event_thread(LIBEVENT_THREAD *me)
{
	me->base = event_init();
	if (!me->base)
	{
		printf("can't allocate event base\n");
		exit(1);
	}

	event_set(&me->notify_event, me->notify_receive_fd, EV_READ|EV_PERSIST, thread_libevent_process, me);
	event_base_set(me->base, &me->notify_event);

	if (-1 == event_add(&me->notify_event, 0))
	{
		printf("can't monitor libevent notify pipe\n");
		exit(1);
	}
	me->new_conn_queue = (conn_queue*)malloc(sizeof(struct conn_queue));
	if (me->new_conn_queue == NULL)
	{
		printf("Failed to allocate memory for connection queue");
		exit(EXIT_FAILURE);
	}

	cq_init(me->new_conn_queue);
}

void thread_libevent_process(int fd, short which, void *arg)
{
	LIBEVENT_THREAD *me = (LIBEVENT_THREAD*)arg;
	CQ_ITEM *item;
	char buf[1];
	if (read(fd, buf, 1) != 1)
		printf("can't read from libevent pipe\n");
	item = cq_pop(me->new_conn_queue);
	if (NULL != item)
	{
		conn *c = conn_new(item->sfd, item->init_state, item->event_flags, item->transport, me->base);

		if (NULL == c)
		{
			if (IS_UDP(item->transport))
			{
				printf("can't listen for events on UDP\n");
				exit(1);
			}
			else
			{
				printf("can't listen for events on fd %d \n", item->sfd);
				close(item->sfd);
			}
		}
		else
		{
			c->thread = me;
			//write(item->read_buffer_size, "a", 1);
		}
		cqi_free(item);
	}
}

void WorkerThreads::create_worker(void *(*func)(void *), void *arg)
{
	pthread_t thread;
	pthread_attr_t attr;
	int ret;
	pthread_attr_init(&attr);
	if ((ret = pthread_create(&thread, &attr, func, arg)) != 0)
	{
		printf("can't create thread");
		exit(1);
	}
}

void* worker_libevent(void *arg)
{
	LIBEVENT_THREAD *me = (LIBEVENT_THREAD*)arg;
	pthread_mutex_lock(&init_lock);
	init_count++;
	pthread_cond_signal(&init_cond);
	pthread_mutex_unlock(&init_lock);
	event_base_loop(me->base, 0);

	return NULL;
}
