#ifndef __NETMESSAGEMANAGER__
#define __NETMESSAGEMANAGER__
#include "cocos2d.h"

class NetMessageManager : public cocos2d::Node
{
public:
	NetMessageManager(void);
	~NetMessageManager(void);

protected:
	virtual void update(float fDelta);

private:
	
};

#endif