#ifndef __GLOBAL__
#define __GLOBAL__
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <list>
#include <set>
#include "proto/responseprotos.pb.h"

using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "../lib/Debug/libprotobuf.lib")
#pragma comment(lib, "../lib/Debug/libprotobuf-lite.lib")
#pragma comment(lib, "../lib/Debug/libprotoc.lib")
#else
#pragma comment(lib, "../lib/Release/libprotobuf.lib")
#pragma comment(lib, "../lib/Release/libprotobuf-lite.lib")
#pragma comment(lib, "../lib/Release/libprotoc.lib")
#endif


#define STATUS_NULL				0x0000
#define STATUS_CONNECTING		0x0001		//��������,infoΪip:port
#define STATUS_CONNECTED		0x0002		//���ӳɹ�,infoΪip:port
#define STATUS_DISCONNECT		0x0004		//����ʧ��,infoΪԭ��
#define STATUS_CONNECTTIMEOUT	0x0008		//���ӳ�ʱ,infoΪip:port
#define STATUS_AUTHING			0x0010		//������֤,infoΪip:port
#define STATUS_AUTHFAIL			0x0020		//��֤ʧ��,infoΪip:port
#define STATUS_AUTHED			0x0040		//��֤�ɹ�,infoΪ��½ʱ��
#define STATUS_INITED			0x0080		//��ʼ�����,infoΪip:port
#define STATUS_UNINIT			0x0100		//��ʼ��δ���,infoΪ��
#define STATUS_KICKED			0x0200		//���������߿ͻ���,infoΪԭ��
#define STATUS_REQUEST			0x0400		//��������,infoΪseq	
#define STATUS_RESPOND			0x0800		//�õ���Ӧ,infoΪseq	
#define STATUS_RESPONDTIMEOUT	0x1000		//��Ӧ��ʱ,infoΪ��Ϣ
#define STATUS_RESPONDERROR		0x2000		//��Ӧ����,infoΪԭ��
#define STATUS_REQUESTERROR		0x4000		//�������,infoΪԭ��
#define STATUS_CLOSE			0x8000		//�ͻ����Զ��Ͽ�,infoΪԭ��
#define STATUS_RECONNECT		0x10000		//�ͻ�������,infoΪ��
#define STATUS_SAMEACCOUNT		0x20000		//�ͻ����ص�½,infoΪ��
#define STATUS_DISACCOUNT		0x40000		//�ͻ����˺ű�����,infoΪ��
#define STATUS_INFO				0x80000		//�ͻ�����Ϣ,infoΪ��Ϣ
#define STATUS_CONNECTFAIL		0x100000	//����ʧ��

template<class T = char>
class autoptr
{
public:
	autoptr(T *buf) : m_buf(buf){}
	~autoptr(){
		delete m_buf;
	}
private:
	T *m_buf;
};

template<class T = char>
class autoptr_arr
{
public:
	autoptr_arr(T *buf) : m_buf(buf){}
	~autoptr_arr(){
		delete []m_buf;
	}
private:
	T *m_buf;
};

class NetworkProxy;

typedef struct tagReserveData
{
	int nReqID;
	NetworkProxy *pNetworkProxy;
} ReserveData;

class ReserveDataMapGuard
{
public:
	ReserveDataMapGuard(map<int, ReserveData*> *m_, map<int, ReserveData*>::iterator it_) 
		: m(m_), it(it_)
	{
	}

	~ReserveDataMapGuard()
	{		
		if (it != m->end())
		{	
			delete it->second;
			m->erase(it);
		}
	}

private:
	map<int, ReserveData*> *m;
	map<int, ReserveData*>::iterator it;
};

typedef struct tagResultNetData
{
	int nSeq;	
	card_protobuf::Response *pResponse;
} ResultNetData;

class CGlobal
{
public:
	CGlobal(void);
	~CGlobal(void);

public:
	int getSeq()
	{
		lock_guard<mutex> lg(m_mutex);
		if (m_nSeq > 10000000)
			m_nSeq = 1;

		return m_nSeq++;
	}
public:
	string				m_strSessionID;
	string				m_strUserName;
	string				m_strUserId;
	string				m_strPassword;
	__int64				m_nDomID;
	int					m_nStatus;
	__int64				m_ComputerID;
	__int64				m_nServerDate;

	map<int, ReserveData*>		m_mapReserveData;

	list<tagResultNetData*>		m_listNetQueue;
	mutex						m_netQueueMutex;

	set<void*>					m_setReqSource;

private:
	int					m_nSeq;
	mutex				m_mutex;
};

#endif
