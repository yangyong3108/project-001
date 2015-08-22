#include "redishelp.h"

#define CONN_URL	"127.0.0.1"
#define REDIS_PORT	6379


RedisHelp::RedisHelp()
{
	m_context = redisConnect(CONN_URL, REDIS_PORT);
	if (m_context != NULL && m_context->err)
	{
		printf("Error: %s\n", redis_context->errstr);
		redisFree(m_context);
		m_context = NULL;
	}
}

RedisHelp::~RedisHelp()
{
	if (m_context != NULL)
		redisFree(m_context);
}

bool RedisHelp::addServerCounter(int &nCount)
{
	if (m_context == NULL)
		return false;

	redisReply* reply = redisCommand(m_context, "incr counter");
	if (reply == NULL)
	{
		printf("ERROR: %s\n", m_context->errstr);
		if (redis_context->err == REDIS_ERR_EOF)
		{
			printf("server closed the redis connection, try connect again\n");
			redisFree(m_context);
			m_context = redisConnect(CONN_URL, REDIS_PORT);
			if (m_context != NULL && m_context->err)
			{
				printf("connect again Error: %s\n", m_context->errstr);
				redisFree(m_context);
				m_context = NULL;
				return false;
			}

			return addServerCounter(nCount);
		}

		return false;
	}
	
	nCount = reply->integer;
	freeReplyObject(reply);
	return true;
}