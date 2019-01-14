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
#include "Utils.h"
#include "ParallelServer.h"
template <class T>
class MyTestClientHandler : public ClientHandler {
private:
    SearcherSolver<T>* solver;
    FileCacheManager<MazeGame<T>*, SearcherSolution*> *cache;
public:
    MyTestClientHandler(SearcherSolver<T> *solver, FileCacheManager<MazeGame<T>*, SearcherSolution*> *cache) {
        this->solver = solver;
        this->cache = cache;
    }

    MyTestClientHandler(SearcherSolver<T> *solver) {
        this->solver = solver;
        this->cache = new FileCacheManager<MazeGame<T>*, SearcherSolution* >("cache.txt");
    }
    virtual int handleClient(Server *server, Client* client) {
        const int commasInPoint = 1;        // number of commas allowed in initial and goal state input
        int elementsInRow;                  // number of elements in row
        vector < string > data;             // data about the maze game
        MazeGame<T>* mazeGame;              // specific maze game problem
        SearcherSolution* solution;         // solution of maze problem
        string buffer;                      // data received by connected client
        /* get data from client */
        do {
            buffer = server->readData(client);
            data.push_back(buffer);
        } while(buffer != END);
        data.pop_back();
        mazeGame = new MazeGame<T>(data);
        /* get solution of this instance of problem */
        if (this->cache->isSolutionExist(mazeGame)) {
            cout << "cache" << endl;
            solution = this->cache->getSolution(mazeGame);
            delete mazeGame;
        } else {
            solution = this->solver->solve(mazeGame);
            this->cache->storeSolution(mazeGame, solution);
        }

        /* send solution to client */
        server->sendData(solution->StringRepresentation(), client);
        return 1;
    }

    virtual ~MyTestClientHandler() {
        if (this->cache != nullptr)
            delete this->cache;
    }

};
#endif
