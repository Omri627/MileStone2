#ifndef PROJECT2_SERIALSERVER_H
    #define PROJECT2_SERIALSERVER_H

#include <iostream>
#include "Server.h"
#include <time.h>

class SerialServer : public Server {
private:
    /* indicate whether the server is running or not */
    bool isRunning;
    /* connect socket file descriptor */
    int socketFd;
    /* client connection file descriptor */
    int clientFd;

    struct create_params {
        Server* server;
        int port;
        int* socketFd;
    };
    int listenToClient();

    static void* listenToClientHelper(void* params);

    void closeClientConnection();

public:
    SerialServer();

    virtual void open(int port, ClientHandler* clientHandler);

    virtual void stop();

};


#endif