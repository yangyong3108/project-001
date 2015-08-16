#ifndef __NETWORKPROXY__
#define __NETWORKPROXY__

#include "proto/commonprotocol.pb.h"
#include "proto/responseprotos.pb.h"
#include "proto/protobufresponse.pb.h"

using namespace card_protobuf;

class NetworkProxy
{
public:
	NetworkProxy(void){}
	virtual ~NetworkProxy(void);

	virtual void OnNetData(int nReqId, Response *pResponse) {};
};

#endif