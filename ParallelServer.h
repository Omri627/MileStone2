//
// Created by ranraboh on 12/01/19.
//

#ifndef PARALLEL_SERVER
#define PARALLEL_SERVER

#include "Server.h"
#include <map>
#include <vector>
#include "Client.h"
#include "ThreadPool.h"

class ParallelServer : public Server {
private:

    struct listen_params {
        Client* client;
        ParallelServer * server;
    };

    map<int, int > serverFd;
    bool firstClient;
    ThreadPool* threadPool;
    bool isRunning;

    bool isConnectedPort(int port);


    void openPortConnection(int port);

    int listenToClient(Client* client);

    static void* listenToClientHelper(void *params);

    static void* interactWithClientHelper(void * params);
public:
    //todo: make private
    int getFd(int port);

    ParallelServer(unsigned long threads);

    virtual void interactWithClient(Client* client);

    virtual void open(int port, ClientHandler *clientHandler);

    virtual void stop();

    virtual void closeClientConnection(Client* client);
};


#endif