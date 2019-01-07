#ifndef PROJECT2_SERIALSERVER_H
#define PROJECT2_SERIALSERVER_H

#include <iostream>
#include "Server.h"
class SerialServer : public Server {
private:
    /* indicate whether the server is running or not */
    bool isRunning;
    /* ip-address of server */
    string address;
    /* socket file descriptor */
    int socketFd;

    int createServer(int port);

    int listenToClient(int socketFd);
public:
    SerialServer(string address);

    SerialServer();

    virtual void open(int port, ClientHandler* clientHandler);

    virtual void stop();

    virtual string readData();

    virtual void sendData(string data);
};


#endif //PROJECT2_SERIALSERVER_H
