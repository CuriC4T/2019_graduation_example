

#include "../header/server.h"
using namespace std;

int main()
{

    printf("start\n");
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

