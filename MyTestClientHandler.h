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
    /* searcher algorithm  */
    SearcherSolver<T>* solver;
    /* file managing storing the solutions of to problems that appeared before */
    FileCacheManager<MazeGame<T>*, SearcherSolution*> *cache;
public:
    /**
     * construct handler object with given solver and cache object
     * @param solver searcher algorithm
     * @param cache file managing storing the solutions of to problems that appeared before
     */
    MyTestClientHandler(SearcherSolver<T> *solver, FileCacheManager<MazeGame<T>*, SearcherSolution*> *cache) {
        this->solver = solver;
        this->cache = cache;
    }
    /**
     * construct handler object with given solver
     * @param solver searcher algorithm.
     */
    MyTestClientHandler(SearcherSolver<T> *solver) {
        this->solver = solver;
        this->cache = new FileCacheManager<MazeGame<T>*, SearcherSolution* >("cache.txt");
    }
    /**
     * handleClient method gets a server and client.
     * and aid the server to handle client request.
     * for any searchable problems, this method processed the data regarding the problem
     * and produce a solution.
     * @param server server object
     * @param client client object
     * @return returns 1 if the this method handle client requests successfully
     * returns 0 if error occured.
     */
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
    /**
     * desructor, used to free memory.
     */
    virtual ~MyTestClientHandler() {
        if (this->cache != nullptr)
            delete this->cache;
        if (this->solver != nullptr) {
            delete solver->getSearcher();
            delete this->solver;
        }

    }

};
#endif
