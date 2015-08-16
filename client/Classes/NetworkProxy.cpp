#include "NetworkProxy.h"
#include "Global.h"

extern CGlobal G;
NetworkProxy::~NetworkProxy(void)
{
	set<void*>::iterator it = G.m_setReqSource.find(this);
	if (it != G.m_setReqSource.end())
		G.m_setReqSource.erase(it);
}