#include "dbhelper.h"
#include <iostream>
#include "global.h"

using namespace pqxx;
using namespace std;

#define CONN_STRING  "dbname=db1 user=dbuser hostaddr=127.0.0.1 port=5432"

result query(const char* szText)
{
	result r;
	try
	{
		connection c(CONN_STRING);
		dbconnguard guard(&c);
		work w(c);
		r = w.exec(szText);
		w.commit();
		return r;
	}
	catch (const exception &e)
	{
		cerr << e.what() <<std::endl;
		return r;
	}

}


