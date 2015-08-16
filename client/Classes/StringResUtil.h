#ifndef __STRINGRESUTIL__
#define __STRINGRESUTIL__
#include "cocos2d.h"

class StringResUtil
{
public:	
	~StringResUtil(void);

	static StringResUtil* instance();

	const char* getStringForKey(const char* szKey, const char* defaultData = NULL) const;

	static void purgeStringResUtil() 
	{
		if (s_instance != NULL)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}

private:
	StringResUtil(void);

private:
	static StringResUtil* s_instance;

	cocos2d::CCDictionary	*m_pValueDict;

};

#endif