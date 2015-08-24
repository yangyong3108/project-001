#ifndef __REDISHELP__
#define __REDISHELP__
#include <hiredis/hiredis.h>

class RedisHelp
{
public:
	RedisHelp(void);
	~RedisHelp(void);

	bool addServerCounter(int &nCount);
	bool connect();
	void disconnect();

	static bool initGameTable();

private:
	redisContext *m_context;
};

#endif
