#ifndef SERVER
    #define SERVER

#include "ClientHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#define END "end"
using namespace std;
class Server {
public:
    pthread_mutex_t global_mutex;

    virtual void open(int port, ClientHandler* clientHandler) = 0;

    virtual string readData() = 0;

    virtual void sendData(string data) = 0;

    virtual void stop() = 0;
};

#endif
