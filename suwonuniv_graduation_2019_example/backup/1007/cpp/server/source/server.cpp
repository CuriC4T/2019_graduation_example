
#include "../header/server.h"
#include "../header/dbmanagement.h"
#include <iostream>
#ifdef __SERVER_H__

using namespace std;

Server::Server()
{
    printf("Create Server...\n");
    DBManagement *dbmanagement = new DBManagement();
    dbmanagement->connectDB("tcp://localhost:3306","hyun","1234","graduationtest");
}
int Server::acceptConnection()
{
    try
    {

        server_socket = socket(PF_INET, SOCK_STREAM, 0);
        if (server_socket == -1)
        {
            errorHandling("server socket error!\n");
        }
        int reuse_address = 1;

        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse_address, sizeof(reuse_address)))
        {
            errorHandling("sokcet setting error!\n");
        }
        //SOL_SOCKET:

        server_addr.sin_addr.s_addr = INADDR_ANY;
        // 모든 주소 허용

        // AF_INET ->  ipv4
        server_addr.sin_family = AF_INET;
        // 포트 셋팅
        server_addr.sin_port = htons(30000);

        if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {

            errorHandling("bind error!\n");
        }
        // passive 대기 상태로 client의 접속을 대기
        // client 에서 connect를 통해 접속 시도 시 3-way handshake 가 일어남
        if (listen(server_socket, MAX_CLIENT) < 0)
        {

            errorHandling("client listening error!\n");
        }
        int clientAddrSize = sizeof(client_addr);
        char msg[BUF_SIZE];

       
        while (true)
        {

            client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&clientAddrSize);
            if (client_socket < 0)
            {
                cout << "client Socket Error" << endl;
            }
            
                cout << "client online..." << endl;
                cout << "Socket: " << client_socket << endl;

                thread client_thread(Server::clientManagement, &client_socket);
                client_thread.join();
                cout << "User end " << client_socket << endl;

        }

    }
    catch (const std::exception &e)
    {
        std::cout << "예외 발생 ! \n"
                  << e.what() << std::endl;
    }
    close(server_socket);
    printf("exit");
    return 0;
}

void *Server::clientManagement(int *socket)
{
    printf("socket!!: %d\n" ,*socket);

    char msg[1024];
    int client_socket = *socket;
    int str_len = 0, i;
    
    bool flag = true;
    while (flag)
    {
        
    //str_len = recv(client_socket, msg, BUF_SIZE - 1, 0);
        str_len=read(client_socket, msg, BUF_SIZE - 1);
        if (str_len == -1){
            cout << "no meesage" << endl;
        }else{
            string message = msg;
            

            printf("%s", msg);
            if (message.compare("exit")==0)
            {
               flag = false;
               strcpy(msg,message.c_str());
               
            }
            cout<<""<<endl;
            write(client_socket, msg, strlen(msg) + 1);
            
        }
        sleep(1);
    }
}
void Server::temp(){

}
void Server::errorHandling(const char *message)
{
    printf("%s", message);
    //fputs(message, stderr);
    //fputs("\n", stderr);
    //exit(1);
}
Server::~Server(){

}

#endif