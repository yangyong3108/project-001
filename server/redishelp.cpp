#include "redishelp.h"
#include "global.h"

#define CONN_URL	"127.0.0.1"
#define REDIS_PORT	6379

static pthread_mutex_t redis_lock = PTHREAD_MUTEX_INITIALIZER;

extern Global G;

bool RedisHelp::initGame()
{
	redisContext *c = redisConnect(CONN_URL, REDIS_PORT);
	rediscontextguard guard(c);
	if (c != NULL && c->err)
	{
		printf("Conn to redis error:%s\n", c->errstr);
		return false;
	}
	redisReply* reply = (redisReply*)redisCommand(c, "exists table:0");
	replyguard rg(reply);

	if (reply == NULL)
	{
		printf("ERROR: %s\n", c->errstr);
		return false;
	}
	if (reply->integer == 0)
	{
		for (int i = 0; i < G.m_nTableCount; i++)
		{
			redisReply* rep = (redisReply*)redisCommand(c, "hmset table:%d capacity %d size %d players %s", i, TABLE_CAPACITY, 0, "");
			replyguard rg(rep);

			if (rep == NULL)
			{
				printf("ERROR: %s\n", c->errstr);
				return false;
			}
		}
	}

	return true;
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
	replyguard rg(reply);
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
	if (reply->type == REDIS_REPLY_INTEGER)
		nCount = reply->integer;

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

bool RedisHelp::getTablePlayers(const int& nTableIndex, vector<string> &vctPlayer)
{
	if (m_context == NULL)
		return false;

	redisReply* reply = (redisReply*)redisCommand(m_context, "hmget table:%d size players", nTableIndex);
	replyguard rg(reply);
	if (reply == NULL)
	{
		printf("ERROR: %s\n", m_context->errstr);
		if (m_context->err == REDIS_ERR_EOF)
		{
			printf("server closed the redis connection, try connect again\n");
			disconnect();
			if (connect())
			{
				return getTablePlayers(nTableIndex, vctPlayer);
			}
		}

		return false;
	}
	
	if (reply->type == REDIS_REPLY_ARRAY)
	{
		if (reply->element[0]->type == REDIS_REPLY_INTEGER)
		{
			const int &nCount = reply->element[0]->integer;
			if (nCount > 0)
			{
				const string &strPlayers = reply->element[1]->str;
				if (nCount * USERID_LENGTH != strPlayers.size())
				{
					printf("ERROR:player count not equal to actual size \n");
					return;
				}
				for (int i = 0; i < nCount; i++)
				{
					vctPlayer.push_back(strPlayers.substr(i * USERID_LENGTH, USERID_LENGTH));
				}
			}
		}
	}
	
	return true;
}

bool RedisHelp::insertPlayerToTable(const int& nTableIndex, const string& strPlayerId)
{
	if (m_context == NULL)
		return false;

	redisReply* reply = (redisReply*)redisCommand(m_context, "hmget table:%d size players", nTableIndex);
	replyguard rg(reply);
	if (reply == NULL)
	{
		printf("ERROR: %s\n", m_context->errstr);
		if (m_context->err == REDIS_ERR_EOF)
		{
			printf("server closed the redis connection, try connect again\n");
			disconnect();
			if (connect())
			{
				return getTablePlayers(nTableIndex, vctPlayer);
			}
		}

		return false;
	}
	
	if (reply->type == REDIS_REPLY_ARRAY)
	{
		if (reply->element[0]->type == REDIS_REPLY_INTEGER)
		{
			const int &nCount = reply->element[0]->integer;
			if (nCount > 0)
			{
				const string &strPlayers = reply->element[1]->str;
				if (nCount * USERID_LENGTH != strPlayers.size())
				{
					printf("ERROR:player count not equal to actual size \n");
					return;
				}
				for (int i = 0; i < nCount; i++)
				{
					vctPlayer.push_back(strPlayers.substr(i * USERID_LENGTH, USERID_LENGTH));
				}
			}
		}
	}
	
	return true;
}