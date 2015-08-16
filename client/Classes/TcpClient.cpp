#include "TcpClient.h"
#include "proto/commonprotocol.pb.h"
#include "proto/requestprotocol.pb.h"
#include "Global.h"
#include <thread>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include "proto/logininfoprotos.pb.h"
#include "proto/responseprotos.pb.h"
#include "proto/protobufresponse.pb.h"

#include "cocos2d.h"
#include "CardScene.h"

#include "NetworkProxy.h"

TcpClient* TcpClient::m_client = NULL;

extern CGlobal G;

using namespace google::protobuf::io;
using namespace card_protobuf;

#define CONN_TIMES	5

TcpClient* TcpClient::instance()
{
	if (m_client == NULL)
		m_client = new TcpClient();

	return m_client;
}

void TcpClient::release()
{
	if (m_client == NULL)
		delete m_client;
}

TcpClient::TcpClient()
	:m_bStop(false)
	,m_bDataReady(false)
{
	m_socket.init();
}

TcpClient::~TcpClient()
{
	m_socket.clean();
}

int TcpClient::start()
{	
	thread t(handleFunc, this);
	t.detach();

	return 0;
}

void* TcpClient::handleFunc(TcpClient* arg)
{
	TcpClient* pClient = (TcpClient*)arg;

	bool bCon(false);
	for (int i = 0; i < CONN_TIMES; i++)
	{
		bCon = pClient->getSocket()->connectToTcp("192.168.208.128", 9999);
		if (bCon)
			break;

		pClient->getSocket()->close();
		//pClient->getSocket()
	}
   
	if (bCon)
	{  
		G.m_nStatus = STATUS_CONNECTED;
		
		thread t(responseFunc, pClient);
		t.detach();		
		while (!pClient->m_bStop)
		{
			unique_lock<mutex> lock(pClient->m_writeMutex);
			if (pClient->m_writeData.getPos() == 0)
				pClient->m_writeCv.wait(lock);

			int nRet = pClient->m_socket.send(pClient->m_writeData.getBuf(), pClient->m_writeData.getPos());
			
			if (nRet < 0)
			{
				pClient->closeAndReConn();
				break;
			}
			else
			{
				pClient->m_writeData.pop(nRet);
			}
		}
		//pClient->requestLogin(G.getSeq());
	}
	else
	{  
        G.m_nStatus = STATUS_DISCONNECT;
    }     
     
    return NULL;      
}

void TcpClient::closeAndReConn()
{
	if (G.m_nStatus & STATUS_AUTHED)
	{
		G.m_nStatus = STATUS_DISCONNECT;
		m_socket.close();
		m_writeData.setPos(0);

		bool bCon(false);
		for (int i = 0; i < CONN_TIMES; i++)
		{
			bCon = m_socket.connectToTcp("192.168.208.128", 9999);
			if (bCon)
				break;

			m_socket.close();
		}
		if (bCon)
		{  
			G.m_nStatus = STATUS_CONNECTED;

			requestLogin();
		}
		else
		{

		}
	}
	else
	{
		G.m_nStatus = STATUS_DISCONNECT;
		m_socket.close();
		m_writeData.setPos(0);

		bool bCon(false);
		for (int i = 0; i < CONN_TIMES; i++)
		{
			bCon = m_socket.connectToTcp("192.168.208.128", 9999);
			if (bCon)
				break;

			m_socket.close();
		}
	}
}

void* TcpClient::responseFunc(TcpClient* arg)
{
	TcpClient* pClient = (TcpClient*)arg;
	DataQueue recvDataQueue;
	int nDataLen(-1);
	while (!pClient->m_bStop)
	{
		char recvBuf[65535];
		int nLen(pClient->getSocket()->recv(recvBuf, sizeof(recvBuf) / sizeof(char), 0));
		if (nLen < 0)
		{

		}
		else
		{
			recvDataQueue.push(recvBuf, nLen);
			int nPos(0);
			int nPackage(recvDataQueue.getPos());

			while (1)
			{
				if (nPackage <= 0)
					break;

				CodedInputStream* coded_input = new CodedInputStream((uint8_t*)(recvDataQueue.getBuf() + nPos), recvDataQueue.getPos() - nPos);
				autoptr<CodedInputStream> inputguard(coded_input);

				int nOldPos = coded_input->CurrentPosition();

				uint32_t datalen;
				if (!coded_input->ReadVarint32(&datalen))
				{
					if (nPos > 0)
					{
						recvDataQueue.pop(nPos);
					}
					break;
				}

				int nNewPos = coded_input->CurrentPosition();
				if (nNewPos + datalen > nPackage)
				{
					//一个包没有收整
					if (nPos > 0)
					{
						recvDataQueue.pop(nPos);
					}

					break;
				}
				else if (nNewPos + datalen == nPackage)
				{
					char* data = new char[datalen];
					autoptr_arr<char> arrdata(data);
					if (coded_input->ReadRaw(data, datalen))
					{
						OnPackage(data, datalen);
					}

					recvDataQueue.setPos(0);
					break;
				}
				else
				{
					char* data = new char[datalen];
					autoptr_arr<char> arrdata(data);

					if (coded_input->ReadRaw(data, datalen))
					{
						OnPackage(data, datalen);
					}

					nPackage -= (datalen+nNewPos-nOldPos);
					nPos += (datalen+nNewPos-nOldPos);
				}
			}
		}
	}

	return NULL;
}

int TcpClient::requestLogin()
{
	TopMessage msgrep;
	msgrep.set_protocol_version("1.0");
	msgrep.set_msg_type(REQUEST);
	msgrep.set_sub_msg_type(LOGIN);
	msgrep.set_session_id(G.m_strSessionID);
	msgrep.set_seq(G.getSeq());

	LoginInfo *pLogin = new LoginInfo();
	autoptr<LoginInfo> loginguard(pLogin);
	pLogin->set_username(G.m_strUserName);
	pLogin->set_password(G.m_strPassword);
	pLogin->set_computerid(G.m_ComputerID);
	pLogin->set_client_version((float)NT_VERSION);

	int nLogin = pLogin->ByteSize();
	char* pStrLogin = new char[nLogin];
	autoptr_arr<char> autoptrLogin(pStrLogin);
	if (!pLogin->SerializeToArray(pStrLogin, nLogin))
	{
		closeAndReConn();
		return 1;
	}

	msgrep.set_data(pStrLogin, pLogin->ByteSize());

	int datalen = msgrep.ByteSize();
	int headlen = CodedOutputStream::VarintSize32(datalen);

	char *buf = new char[datalen];
	autoptr_arr<char> arrguard(buf);
	if (!msgrep.SerializeToArray(buf, datalen))
	{
		closeAndReConn();
		return 1;
	}

	//char *tmpArr = new char[datalen+headlen];
	//autoptr_arr<char> arrguard2(tmpArr);
	lock_guard<mutex> lg(m_writeMutex);
	if (m_writeData.expand(datalen+headlen))
	{
		ZeroCopyOutputStream* raw_output = new ArrayOutputStream(m_writeData.getBuf() + m_writeData.getPos(), datalen+headlen);
		CodedOutputStream* coded_output = new CodedOutputStream(raw_output);
		coded_output->WriteVarint32(datalen);
		coded_output->WriteRaw(buf, datalen);	
		m_writeData.setPos(m_writeData.getPos() + (datalen+headlen));
		//m_writeData.push(tmpArr, datalen+headlen);
		//ReserveData *pReserveData = new ReserveData;
		//pReserveData->pNetworkProxy = pData;
		//pReserveData->nReqID = nReqId;
		//G.m_mapReserveData.insert(map<int, ReserveData*>::value_type(nSeq, pReserveData));
		//G.m_setReqSource.insert(pData);
		m_writeCv.notify_one();

		delete coded_output;
		delete raw_output;
	}

	return 0;
}

//int TcpClient::requestLogin(int nSeq, int nReqId, NetworkProxy *pData)
//{
//	TopMessage msgrep;
//	msgrep.set_protocol_version("1.0");
//	msgrep.set_msg_type(REQUEST);
//	msgrep.set_sub_msg_type(LOGIN);
//	msgrep.set_session_id(G.m_strSessionID);
//	msgrep.set_seq(nSeq);
//
//	LoginInfo *pLogin = new LoginInfo();
//	autoptr<LoginInfo> loginguard(pLogin);
//	pLogin->set_username(G.m_strUserName);
//	pLogin->set_password(G.m_strPassword);
//	pLogin->set_computerid(G.m_ComputerID);
//	pLogin->set_client_version((float)NT_VERSION);
//
//	int nLogin = pLogin->ByteSize();
//	char* pStrLogin = new char[nLogin];
//	autoptr_arr<char> autoptrLogin(pStrLogin);
//	if (!pLogin->SerializeToArray(pStrLogin, nLogin))
//	{
//		m_socket.close();
//		return 1;
//	}
//
//	msgrep.set_data(pStrLogin, pLogin->ByteSize());
//
//	int datalen = msgrep.ByteSize();
//	int headlen = CodedOutputStream::VarintSize32(datalen);
//
//	char *buf = new char[datalen];
//	autoptr_arr<char> arrguard(buf);
//	if (!msgrep.SerializeToArray(buf, datalen))
//	{
//		m_socket.close();
//		return 1;
//	}
//
//	//char *tmpArr = new char[datalen+headlen];
//	//autoptr_arr<char> arrguard2(tmpArr);
//	lock_guard<mutex> lg(m_writeMutex);
//	if (m_writeData.expand(datalen+headlen))
//	{
//		ZeroCopyOutputStream* raw_output = new ArrayOutputStream(m_writeData.getBuf() + m_writeData.getPos(), datalen+headlen);
//		CodedOutputStream* coded_output = new CodedOutputStream(raw_output);
//		coded_output->WriteVarint32(datalen);
//		coded_output->WriteRaw(buf, datalen);	
//		m_writeData.setPos(m_writeData.getPos() + (datalen+headlen));
//		//m_writeData.push(tmpArr, datalen+headlen);
//		ReserveData *pReserveData = new ReserveData;
//		pReserveData->pNetworkProxy = pData;
//		pReserveData->nReqID = nReqId;
//		G.m_mapReserveData.insert(map<int, ReserveData*>::value_type(nSeq, pReserveData));
//		G.m_setReqSource.insert(pData);
//		m_writeCv.notify_one();
//
//		delete coded_output;
//		delete raw_output;
//	}
//
//	return 0;
//}

int TcpClient::requestData(const int seq, const string& version, const string& package, const string& func, const string& arg)
{
	TopMessage msgrep;
	msgrep.set_protocol_version("1.0");
	msgrep.set_msg_type(REQUEST);
	msgrep.set_sub_msg_type(POST);
	msgrep.set_session_id(G.m_strSessionID);
	msgrep.set_seq(seq);
	msgrep.set_host(m_strIP);
	msgrep.set_user_name(G.m_strUserName);
	msgrep.set_version((float)NT_VERSION);
	
	Request req;
	req.set_domid(G.m_nDomID);
	req.set_package_version(version);
	req.set_package(package);
	req.set_function(func);
	req.set_arg(arg);

	int datalen = req.ByteSize();
	char *buf = new char[datalen];
	autoptr_arr<char> arrguard1(buf);
	if (!req.SerializeToArray(buf, datalen))
	{
		G.m_nStatus = STATUS_CLOSE;
		//NT_STATUS("OnConnectError");

		m_socket.close();
		return 1;
	}

	msgrep.set_data(buf, datalen);

	datalen = msgrep.ByteSize();
	int headlen = CodedOutputStream::VarintSize32(datalen);

	char *databuf = new char[datalen];
	autoptr_arr<char> arrguard(databuf);
	if (!msgrep.SerializeToArray(databuf, datalen))
	{
		G.m_nStatus = STATUS_CLOSE;
		//NT_STATUS("OnConnectError");

		m_socket.close();
		return 1;
	}

	char *tmpArr = new char[datalen+headlen];
	autoptr_arr<char> arrguard2(tmpArr);
	ZeroCopyOutputStream* raw_output = new ArrayOutputStream(tmpArr, datalen+headlen);
	CodedOutputStream* coded_output = new CodedOutputStream(raw_output);
	coded_output->WriteVarint32(datalen);
	coded_output->WriteRaw(databuf, datalen);

	if (!m_socket.send(tmpArr, datalen + headlen))
	{
		//发送错误
		G.m_nStatus = STATUS_CLOSE;
		//NT_STATUS("OnConnectError");

		delete coded_output;
		delete raw_output;

		m_socket.close();
		return 1;
	}

	delete coded_output;
	delete raw_output;

	return 0;
}

void TcpClient::OnPackage(const char *buf, size_t len)
{
	if (buf == NULL || len <= 0)
		return;

	TopMessage msg;
	if(!msg.ParseFromArray(buf, len))
		return;

	__int64 seq = msg.seq();
	switch (msg.msg_type())
	{
	default:
		break;
	case RESPONSE:
		{
			switch (msg.sub_msg_type())
			{
			default:
				break;
			case LOGIN:
				{
					/*Response *pLoginResponse = new Response;
					if (!pLoginResponse->ParseFromString(msg.data()))
					{
						delete pLoginResponse;
						return;
					}
					ResultNetData *pResultNetData = new ResultNetData;
					pResultNetData->nSeq = seq;
					pResultNetData->pResponse = pLoginResponse;
					lock_guard<mutex> lg(G.m_netQueueMutex);
					G.m_listNetQueue.push_back(pResultNetData);
					G.m_nServerDate = msg.timestamp();*/

					Response loginResponse;
					if (!loginResponse.ParseFromString(msg.data()))
					{
						return;
					}
					G.m_nServerDate = msg.timestamp();

					if (loginResponse.response_code() == OK)
					{
						G.m_nServerDate = msg.timestamp();
						G.m_nStatus = STATUS_AUTHED;
						for (int idx = 0; idx < loginResponse.data_size(); idx++)
						{
							Data crdata = loginResponse.data(idx);
							ProtobufResponseData pbrd;

							if (idx == 0)
							{
								if(crdata.type() == PROTOBUF)
								{
									if (!pbrd.ParseFromString(crdata.value()))
									continue;
								}
								else
									continue;

								for(int i = 0; i < pbrd.rowvalue_size(); i++)
								{
									RowValue rowValue = pbrd.rowvalue(i);
									for(int j = 0; j < rowValue.columnvalue_size(); j++)
									{
										RowValue_ColumnValue columnValue = rowValue.columnvalue(j);
										if (pbrd.columninfo(j).name() == "money")
										{

										}
										else if (pbrd.columninfo(j).name() == "username")
										{
											G.m_strUserName = columnValue.stringvalue();
										}
										else if (pbrd.columninfo(j).name() == "userid")
										{
											G.m_strUserId = columnValue.stringvalue();
										}
									}
								}
							}
						}
						cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([]
						{
							//G.m_mapReserveData.find(nSeq);
							auto scene = CardScene::createScene();
							cocos2d::Director::getInstance()->replaceScene(scene);
						}
						); 
					}
					else if (loginResponse.response_code() == NOT_FOUND)
					{

					}
				}
				break;
			case POST:
				{
					Response *pLoginResponse = new Response;
					if (!pLoginResponse->ParseFromString(msg.data()))
					{
						delete pLoginResponse;
						return;
					}
					ResultNetData *pResultNetData = new ResultNetData;
					pResultNetData->nSeq = seq;
					pResultNetData->pResponse = pLoginResponse;
					lock_guard<mutex> lg(G.m_netQueueMutex);
					G.m_listNetQueue.push_back(pResultNetData);
					G.m_nServerDate = msg.timestamp();
				}
				break;
			}
		}
		break;
	}

}