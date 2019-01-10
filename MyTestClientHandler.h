#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "StringReverserSolver.h"
#include "Server.h"
#include "FileCacheManager.h"
#include "SearcherSolver.h"
#include "SearcherSolution.h"
#include "MazeGame.h"

template <class T>
class MyTestClientHandler : public ClientHandler {
private:
    SearcherSolver<T>* solver;
    FileCacheManager<MazeGame<T>*, Solution*> *cache;
public:
    MyTestClientHandler(SearcherSolver<T> *solver, FileCacheManager<MazeGame<T>*, Solution*> *cache);

    MyTestClientHandler(SearcherSolver<T> *solver);

    virtual void handleClient(Server *server);

    virtual ~MyTestClientHandler();

};
#endif