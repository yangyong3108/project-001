#ifndef __DATAQUEUE__
#define __DATAQUEUE__
#include <stdio.h>
#include <stdlib.h>

class DataQueue
{
public:
	DataQueue(void);
	~DataQueue(void);

	int getPos() { return m_nPos; };
	char* getBuf() { return m_buf; }
	void setPos(int nPos) { m_nPos = nPos; }
	bool push(const char *sz, size_t len);
	void pop(size_t len);
	bool expand(size_t len);

private:
	int m_nPos;
	int m_nSize;
	char *m_buf;
};

#endif
