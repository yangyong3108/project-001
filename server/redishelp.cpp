#include "redishelp.h"
#include "global.h"

#define CONN_URL	"127.0.0.1"
#define REDIS_PORT	6379

bool RedisHelp::initGameTable()
{
	redisContext *c = redisConnect(CONN_URL, REDIS_PORT);
	rediscontextguard guard(c);
	if (c != NULL && c->err)
	{
		printf("Conn to redis error:%s\n", c->errstr);
		return false;
	}
	
}

RedisHelp::RedisHelp(void)
{
}

RedisHelp::~RedisHelp(void)
{
}

bool RedisHelp::addServerCounter(int &nCount)
{
	if (m_context == NULL)
		return false;

	redisReply* reply = (redisReply*)redisCommand(m_context, "incr counter");
	if (reply == NULL)
	{
		printf("ERROR: %s\n", m_context->errstr);
		if (m_context->err == REDIS_ERR_EOF)
		{
			printf("server closed the redis connection, try connect again\n");
			disconnect();
			if (connect())
			{
				return addServerCounter(nCount);
			}
		}

		return false;
	}
	
	nCount = reply->integer;
	freeReplyObject(reply);
	return true;
}

bool RedisHelp::connect()
{
	printf("conn to redis\n");
	m_context = redisConnect(CONN_URL, REDIS_PORT);
	if (m_context != NULL && m_context->err)
	{
		printf("CONN REDIS Error: %s\n", m_context->errstr);
		redisFree(m_context);
		m_context = NULL;
		return false;
	}
	return true;
}


void RedisHelp::disconnect()
{
	printf("disconn to redis\n");
	if (m_context != NULL)
	{
		redisFree(m_context);
		m_context = NULL;
	}
	
}
