

#include "../header/server.h"
using namespace std;

int main()
{

    printf("start\n");
    //DBManagement *dbmanagement = new DBManagement();
    //dbmanagement->connectDB("tcp://localhost:3306","hyun","1234","graduationtest");
    //dbmanagement->selectData("keyword","hello");
    //Server *server = new Server();
    //string s="hello.txt";
    //string aa =server->loadFile(s);

    Server *server = new Server();
    int result = server->acceptConnection();
    switch (result)
    {
    case -1:
        printf("error\n");
        break;

    default:
        printf("end\n");
        break;
    }
    return 0;
}

