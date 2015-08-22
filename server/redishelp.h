#ifndef __REDISHELP__
#define __REDISHELP__
#include <hiredis/hiredis.h>


class RedisHelp
{
public:
	RedisHelp();
	~RedisHelp();

	bool addServerCounter(int &nCount);

private:
	redisContext *m_context;
};

#endif