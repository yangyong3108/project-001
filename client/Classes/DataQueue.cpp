#include "DataQueue.h"
#include <string>

#define PER_SIZE	512

DataQueue::DataQueue(void)
	:m_nPos(0)
	,m_nSize(0)
	,m_buf(NULL)
{

}

DataQueue::~DataQueue(void)
{
	delete m_buf;
}

bool DataQueue::push(const char *sz, size_t len)
{
	if (!expand(len))
		return false;

	memcpy(m_buf + m_nPos, sz, len);
	m_nPos += len;
}

void DataQueue::pop(size_t len)
{
	if (!m_buf)
		return;

	memcpy(m_buf, m_buf + len, m_nPos - len);
	m_nPos -= len;
}

bool DataQueue::expand(size_t len)
{
	if ((m_nPos + len) > m_nSize)
	{
		int newSize( ((m_nPos + len) / PER_SIZE + 1)  * PER_SIZE );
		char *buf = (char*)realloc(m_buf, newSize);
		if (buf == NULL)
			return false;
		m_buf = buf;
		m_nSize = newSize;
	}

	return true;
}