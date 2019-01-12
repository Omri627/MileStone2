#ifndef PROJECT2_CLIENT_H
#define PROJECT2_CLIENT_H

#include "ClientHandler.h"
class Client {
private:
    int port;
    int connectionFd;
    ClientHandler *handler;
    int end;
public:
    Client(int port, int connectionFd, ClientHandler *clientHandler);

    Client(int port, ClientHandler *clientHandler);

    int getPort() const;

    void setPort(int port);

    int getConnectionFd() const;

    void setConnectionFd(int connectionFd);

    ClientHandler *getHandler() const;

    void setHandler(ClientHandler *handler);

    int getEnd() const;

    void setEnd(int end);

    void send(Server *server, string data);

    string readData(Server *server);

    virtual ~Client();
};

#endif