#ifndef __REDISHELP__
#define __REDISHELP__
#include <hiredis/hiredis.h>
#include <vector>
#include <string>
using namespace std;

class RedisHelp
{
public:
	RedisHelp(void);
	~RedisHelp(void);

	bool addServerCounter(int &nCount);
	bool connect();
	void disconnect();
	bool getTablePlayers(const int& nTableIndex, vector<string> &vctPlayer);
	bool insertPlayerToTable(const int& nTableIndex, const string& strPlayerId);
	bool getTableInfo(ProtobufResponseData &tableInfo);

	static bool initGame();


private:
	redisContext *m_context;
};

#endif
