#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "StringReverserSolver.h"
#include "Server.h"

class MyTestClientHandler : public ClientHandler {
private:
    StringReverserSolver* solver;
    CacheManager<string, string>* cache;
public:
    MyTestClientHandler(StringReverserSolver* solver, CacheManager<string, string> *cache);

    virtual void handleClient(string problem, Server * server);



};
#endif