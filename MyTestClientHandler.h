#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

class MyTestClientHandler : public ClientHandler {
private:
    Solver<string, string>* solver;
    CacheManager<string, string>* cache;
public:
    MyTestClientHandler(Solver<string, string>* solver);

};
#endif