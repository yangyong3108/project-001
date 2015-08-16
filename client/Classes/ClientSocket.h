#ifndef __CLIENTSOCKET__
#define __CLIENTSOCKET__

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

typedef int SOCKET;
#define INVALID_SOCKET	-1

#endif

#define SOCKET_ERR		-1
#define SOCKET_OK		0

class ClientSocket
{
public:
	ClientSocket()
		:m_socket(INVALID_SOCKET){}
	~ClientSocket(){ close(); }

	static int init();
	static int clean();

	bool create(int af, int type, int protocol = 0);
	bool connectToTcp(const char* ip, unsigned short port);
	int send(const char* buf, int len, int flags = 0);
	int recv(char* buf, int len, int flags = 0);
	int close();
	int getError();

private:
	SOCKET		m_socket;
	fd_set		m_fdR;
};

#endif