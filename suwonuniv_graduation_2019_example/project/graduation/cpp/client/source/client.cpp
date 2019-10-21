#include "../header/client.h"
#include <iostream>

#ifdef __CLIENT_H__
using namespace std;

Client::Client()
{
    printf("start client....");
}
Client::~Client()
{
    close(client_socket);
}
void Client::initClient()
{
    try
    {
        printf("client start...\n");
        client_socket = socket(PF_INET, SOCK_STREAM, 0);
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(30000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            errorHandling("client connect error!\n");
        }
        else
        {
            printf("connect: %d\n", client_socket);
            thread client_thread(Client::clientThread, &client_socket);
            client_thread.join();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //read(client_socket, buff, BUFF_SIZE);
    //printf("%s\n", buff);
}
void Client::connectServer()
{
    printf("asd");
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

void Client::clientThread(int *socket)
{
    int client_socket = *socket;
    char msg[1024];
    bool flag = true;
    string message;
    if (client_socket != -1)
    {
        while (flag)
        {
            cout<<"input message: "<<endl;
            cin>>msg;
            write(client_socket, msg, strlen(msg) + 1);
            read(client_socket, msg, 100 - 1);
            printf("FromServer: %s\n", msg);
            message =msg;
            if(message.compare("exit")==0){
                flag=false;
                
            }else if(message.compare("Select File!")==0){
                char token[] ="filename#";

                cout<<"input file name: "<<endl;
                cin>>msg;
                strcat(token,msg);
                write(client_socket, token, strlen(token) + 1);
                read(client_socket, msg, 100 - 1);
                message =msg;
                vector<string> result;
                printf("FromServer: %s\n", msg);
                result=tokenize_getline(message);
                if(result[0].compare("searchedfile")==0){
                    cout<<result[1]<<endl;
                }
            }else {
                
                
            }
        }
    }
}
void Client::errorHandling(const char *message)
{
    printf("%s", message);
    exit(1);
}

#endif