# include "../header/dbmanagement.h"

DBManagement::DBManagement(){

}
DBManagement::~DBManagement(){
    delete res;
    delete stmt;
    delete conn;
}
void DBManagement::connectDB(string domain,string user,string passwd,string dbname){
    try {
        cout<<"Connecting DB......"<<endl;

        driver=get_driver_instance();
        conn=driver->connect(domain,user,passwd);
        if(conn!=NULL){
            cout<<"DB Connection Susseccful!"<<endl;
        }
        else{
            cout<<"DB Connection Fail"<<endl;

        }
        conn->setSchema(dbname);
        stmt=conn->createStatement();
 
       
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}
void DBManagement::insertData(string tbname,string values){
    try {
        stmt->execute("insert into"+tbname+" values"+'('+values+");");
 
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
 
        cout <<"ERR CMD : "<<"insert into"+tbname+" values"+'('+values+");"<<endl;
    }

}