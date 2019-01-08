#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "StringReverserSolver.h"
#include "Server.h"
#include "FileCacheManager.h"


class MyTestClientHandler : public ClientHandler {
private:
    StringReverserSolver *solver;
    FileCacheManager<string, string> *cache;
public:
    MyTestClientHandler(StringReverserSolver *solver, FileCacheManager<string, string> *cache);

    MyTestClientHandler(StringReverserSolver *solver);

    virtual void handleClient(string problem, Server *server);

    virtual ~MyTestClientHandler();
};
#endif