#include "NetMessageManager.h"
#include "Global.h"
#include "NetworkProxy.h"

extern CGlobal G;

NetMessageManager::NetMessageManager(void)
{
	onEnter();
	onEnterTransitionDidFinish();
	scheduleUpdate();
}

NetMessageManager::~NetMessageManager(void)
{

}

void NetMessageManager::update(float fDelta)
{
	lock_guard<mutex> lg(G.m_netQueueMutex);	
	if (G.m_listNetQueue.empty())
		return;
	ResultNetData* pResultNetData(G.m_listNetQueue.front());
	G.m_listNetQueue.pop_front();
	autoptr<ResultNetData> resultNetDataGuard(pResultNetData);

	const int &nSeq = pResultNetData->nSeq;
	map<int, ReserveData*>::iterator itReserve(G.m_mapReserveData.find(nSeq));
	if (itReserve == G.m_mapReserveData.end())
		return;
	ReserveDataMapGuard reserveDataMapGuard(&G.m_mapReserveData, itReserve);

	ReserveData *pReserveData(itReserve->second);
	
	if (G.m_setReqSource.find((pReserveData->pNetworkProxy)) == G.m_setReqSource.end())
		return;

	if (pReserveData->pNetworkProxy == NULL)
		return;

	pReserveData->pNetworkProxy->OnNetData(itReserve->second->nReqID, pResultNetData->pResponse);
	
}