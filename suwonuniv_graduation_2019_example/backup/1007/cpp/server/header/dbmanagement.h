# ifndef __DBMANAGEMENT_H__
# define __DBMANAGEMENT_H__

# include <mysql_connection.h> 
# include <cppconn/driver.h> 
# include <cppconn/exception.h> 
# include <cppconn/resultset.h> 
# include <cppconn/statement.h> 
# include <iostream>
 
 using namespace std;

class DBManagement{
    

    public:
        sql::Driver *driver;
        sql::Connection *conn;
        sql::Statement *stmt;
        sql::ResultSet *res;
        DBManagement();
        ~DBManagement();
        void connectDB(string domain,string user,string passwd,string dbname);
        void insertData(string tbname,string values);
    private:
        
    

};


# include "../source/dbmanagement.cpp"
# endif