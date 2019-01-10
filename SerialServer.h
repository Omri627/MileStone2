#ifndef PROJECT2_SERIALSERVER_H
    #define PROJECT2_SERIALSERVER_H

#include <iostream>
#include "Server.h"
#include <time.h>

class SerialServer : public Server {
private:
    /* indicate whether the server is running or not */
    bool isRunning;
    /* ip-address of server */
    string address;
    /* connect socket file descriptor */
    int socketFd;
    /* client connection file descriptor */
    int clientFd;

    struct create_params {
        SerialServer* server;
        int port;
    };
    int createServer(int port);

    static void* createServerHelper(void* params);

    int listenToClient();

    static void* listenToClientHelper(void* params);

    void closeClientConnection();

public:
    SerialServer(string address);

    SerialServer();

    virtual void open(int port, ClientHandler* clientHandler);

    virtual void stop();

    virtual string readData();

    virtual void sendData(string data);

};


#endif