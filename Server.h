#ifndef SERVER
    #define SERVER

#include "ClientHandler.h"
#include "Client.h"
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

    struct create_params {
        Server* server;
        int port;
        int* socketFd;
    };
    static void* createServerHelper(void* params);

    virtual int createPortConnection(int port);

    virtual string readData(Client* client);

    virtual void sendData(string data, Client* client);

    virtual void open(int port, ClientHandler* clientHandler) = 0;

    virtual void stop() = 0;
};

#endif
