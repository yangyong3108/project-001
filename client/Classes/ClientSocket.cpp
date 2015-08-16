#include "ClientSocket.h"

#ifdef WIN32
#pragma comment(lib, "wsock32")
#endif

int ClientSocket::init()
{
#ifdef WIN32
	/*
	 http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
	 typedef struct WSAData {
	 WORD wVersion;								//winsock version
	 WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
	 char szDescription[WSADESCRIPTION_LEN+1];
	 char szSystemStatus[WSASYSSTATUS_LEN+1];
	 unsigned short iMaxSockets;
	 unsigned short iMaxUdpDg;
	 char FAR * lpVendorInfo;
	 }WSADATA, *LPWSADATA;
	 */
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8))
	WORD version = MAKEWORD(2, 2);
	int ret = WSAStartup(version, &wsaData); //win sock start up
	if (ret != 0) 
	{
		return -1;
	}
#endif

	return 0;
}

int ClientSocket::clean()
{
#ifdef WIN32
	return (WSACleanup());
#endif
	return 0;
}

bool ClientSocket::create(int af, int type, int protocol)
{
	m_socket = socket(af, type, protocol);
	if (m_socket == INVALID_SOCKET)
		return false;
	
	//int iOptionVal = 1; // Turn on Keep Alive
	//int iOptLen = sizeof(iOptionVal);
	//if (setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&iOptionVal, iOptLen) == SOCKET_ERROR) // Turn on Keep Alive
	//{
	//	return -1;
	//}
	//else
	//{
	//	// Reset the value of Keep Alive
	//	tcp_keepalive inKeepAlive;
	//	inKeepAlive.onoff = 1;
	//	inKeepAlive.keepalivetime = KEEPALIVEIDLE; // 30'
	//	inKeepAlive.keepaliveinterval = KEEPALIVEINTERVAL; // 2'
	//	
	//	unsigned long ulInLen = sizeof(tcp_keepalive);
	//	tcp_keepalive outKeepAlive = {0};
	//	unsigned long ulOutLen = sizeof(tcp_keepalive);
	//	unsigned long ulBytesReturn = 0;
	//	
	//	// Reset the value
	//	if (WSAIoctl(m_socket, SIO_KEEPALIVE_VALS, (LPVOID)&inKeepAlive, ulInLen, 
	//		(LPVOID)&outKeepAlive, ulOutLen, 
	//		&ulBytesReturn, NULL, NULL) == SOCKET_ERROR) 
	//	{
	//		TRACE("WSAIoctl failed. error code = %d", WSAGetLastError()); 
	//		return -1;
	//	}
	//}


	return true;
}

bool ClientSocket::connectToTcp(const char* ip, unsigned short port)
{
	if (!create(AF_INET, SOCK_STREAM, 0))
		return false;

	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = ::connect(m_socket, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if (ret == SOCKET_ERROR) 
		return false;

	return true;
}

int ClientSocket::send(const char* buf, int len, int flags)
{
	/*int nWrote(0), count(0);
	while (count < len)
	{
		nWrote = ::send(m_socket, buf + count, len - count, flags);
		if (nWrote == -1 || nWrote == 0)
			return false;
		count += nWrote;
	}*/

	return (::send(m_socket, buf, len, flags));
}

int ClientSocket::recv(char* buf, int len, int flags)
{
	return (::recv(m_socket, buf, len, flags));
}

int ClientSocket::close()
{
	int nRet(0);
#ifdef WIN32
	nRet = (::closesocket(m_socket));
#else
	nRet = (::close(m_socket));
#endif
	m_socket = INVALID_SOCKET;
	return nRet;
}

int ClientSocket::getError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return -1;
#endif
}