#include "UserData.h"

UserData* UserData::s_userdata = NULL;

UserData::UserData(void)
	:m_nUserId(0)
{

}

UserData* UserData::instance()
{
	if (s_userdata == NULL)
		s_userdata = new UserData();

	return s_userdata;
}

void UserData::release()
{
	if (s_userdata != NULL)
		delete s_userdata;
}