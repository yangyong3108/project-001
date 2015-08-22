#include <iostream>
//#include <pqxx/pqxx>
#include "dbhelper.h"

int main()
{
	try
	{
		//pqxx::connection c("dbname=db1 user=dbuser password=12345678yy hostaddr=127.0.0.1 port=5432");
		//if (c.is_open())
		//  std::cout << "Opened database successfully:"<<c.dbname()<<std::endl;
		//pqxx::work w(c);
		//pqxx::result r = w.exec("SELECT * from t_user");
		//w.commit();
        pqxx::result r = query("SELECT * from t_user");
		std::cout << r[0][1].c_str() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() <<std::endl;
		return 1;
	}
}
