
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
vector<string> tokenize_getline(const string& data, const char delimiter = '#') {
	vector<string> result;
	string token;
	stringstream ss(data);

	while (getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}
void *Server::clientManagement(int *socket)
{

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
            

            if (message.compare("exit")==0)
            {
               flag = false;
               strcpy(msg,message.c_str());
               
            }else if(message.compare("search")==0){
                message="Select File!";


                strcpy(msg,message.c_str());
            }else if(message.compare("help")==0){
                message="Commend: \n\r1. search\n\r2. help\n\r3. exit\n\r";
                strcpy(msg,message.c_str());
            }else {
                vector<string> result;
                string fromdb;
                result=tokenize_getline(message);
                if(result[0].compare("filename")==0){
                    fromdb=loadFile(result[1]);
                    cout<<fromdb<<endl;

                    if(!fromdb.empty()){
                        char token[]="searchedfile#";
                        strcat(token,fromdb.c_str());
                        printf("hhhhhhhhh%s",token);
                        strcpy(msg,token);
                    }
                    else{
                        strcpy(msg,"no such file");
                    }
                }else{
                    strcpy(msg,"no such commend");
                }
            }
            cout<<""<<endl;
            write(client_socket, msg, strlen(msg) + 1);
            
        }
        sleep(1);
    }
}



string Server::loadFile(string filename){
    string path="../../file/";
    if(!filename.empty()){
        path=path+filename;
        ifstream in(path);
        string s;

        if (in.is_open()) {
        // 위치 지정자를 파일 끝으로 옮긴다.
            in.seekg(0, ios::end);

            // 그리고 그 위치를 읽는다. (파일의 크기)
            int size = in.tellg();

            // 그 크기의 문자열을 할당한다.
            s.resize(size);

            // 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
            in.seekg(0, ios::beg);

            // 파일 전체 내용을 읽어서 문자열에 저장한다.
            in.read(&s[0], size);
            return s;
        } else {
            cout << "파일을 찾을 수 없습니다!" << std::endl;
            return NULL;
        }
    }else{
        return NULL;
    }
    

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