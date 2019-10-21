#ifndef __SERVER_H__
#define __SERVER_H__

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include <string>
#include "time.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "pthread.h"
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#define BUF_SIZE 100
#define MAX_CLIENT 10
#define MAX_IP 10

class Server
{

private:
    int server_socket;
    int client_socket;
    struct sockaddr_in server_addr, client_addr;
    pthread_t t_id;
    pthread_mutex_t mutx;

public:
    Server();
    int acceptConnection();
    static void *clientManagement(int *socket);
    void errorHandling(const char *message);
    static std::string loadFile(std::string filename);
    ~Server();
};
#include "../source/server.cpp"
#endif