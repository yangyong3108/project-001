#ifndef __GLOBAL__
#define __GLOBAL__

#include <pqxx/pqxx>
//#include <hiredis/hiredis.h>

template<class T = char>
class autoptr
{
	public:
		autoptr(T* ptr):m_ptr(ptr) { }
		~autoptr() { delete m_ptr; }

	private:
		T* m_ptr;
};

template<class T = char>
class autoptr_arr
{
	public:
		autoptr_arr(T* arr) : m_ptr(arr){}
		~autoptr_arr(){ delete [] m_ptr; }
	private:
		T* m_ptr;
};

class dbconnguard
{
	public:
		dbconnguard(pqxx::connection* c) : m_conn(c){}
		~dbconnguard(){ m_conn->disconnect(); }

	private:
		pqxx::connection* m_conn;
};

//class rediscontextguard
//{
//public:
//	rediscontextguard(redisContext* c) : m_context(c){}
//	~rediscontextguard() { redisFree(m_context); }
//private:
//	redisContext *m_context;
//};

#endif
