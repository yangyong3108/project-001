#ifndef __DBHELPER__
#define __DBHELPER__
#include <pqxx/pqxx>

pqxx::result query(const char* szText);

#endif
