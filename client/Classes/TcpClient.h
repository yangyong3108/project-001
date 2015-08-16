#ifndef __TCPCLIENT__
#define __TCPCLIENT__

#include "ClientSocket.h"
#include <string>
#include <condition_variable>
#include <mutex>
#include "DataQueue.h"

using namespace std;

#define NT_VERSION					1.1

class NetworkProxy;
class TcpClient
{
public:
	static TcpClient* instance();
	static void release();
	~TcpClient();
	ClientSocket* getSocket() { return &m_socket; }
	int start();

	int requestData(const int seq, const string& version, const string& package, const string& func, const string& arg);
	int requestLogin();

	void closeAndReConn();

private:
	TcpClient();
	static void* handleFunc(TcpClient* arg);
	static void* responseFunc(TcpClient* arg);
	static void OnPackage(const char *buf, size_t len);
public:
	bool				m_bStop;
	condition_variable	m_writeCv;
	mutex				m_writeMutex;
	DataQueue			m_writeData;
	bool				m_bDataReady;

private:
	static TcpClient *m_client;
	ClientSocket m_socket;
	string m_strIP;
};


#endif