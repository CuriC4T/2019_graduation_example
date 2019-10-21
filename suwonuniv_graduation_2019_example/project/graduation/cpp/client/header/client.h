#pragma once
#ifndef __CLIENT_H__
#define __CLIENT_H__


#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
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

class Client
{
private:
    int client_socket;
    struct sockaddr_in server_addr;
    char message[100];
public:
    Client();
    ~Client();
    void initClient();
    void connectServer();
    static void clientThread(int *socket);
    void errorHandling(const char *message);
};

#include "../source/client.cpp"
#endif