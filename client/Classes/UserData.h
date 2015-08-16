#ifndef __USERDATA__
#define __USERDATA__
#include <string>


class UserData
{
public:
	static UserData* instance();
	static void release();
	std::string m_userName;
	int			m_nUserId;

private:
	UserData(void);

private:
	static UserData*	s_userdata;
};

#endif