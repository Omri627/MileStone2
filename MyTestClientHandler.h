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
    MyTestClientHandler(SearcherSolver<T> *solver, FileCacheManager<MazeGame<T>*, Solution*> *cache) {
        this->solver = solver;
        this->cache = cache;
    }

    MyTestClientHandler(SearcherSolver<T> *solver) {
        this->solver = solver;
        this->cache = new FileCacheManager<MazeGame<T>*, Solution* >("cache.txt");
    }

    virtual void handleClient(Server *server) {
        MazeGame<T>* mazeGame;             // maze game
        int linesInput;                    // number of lines
        Solution* solution;        // solution of maze
        vector < string > data;            // data about the maze game
        linesInput = atoi(server->readData().c_str()) + 2;
        for (int i = 0 ; i < linesInput; i++) {
            data.push_back(server->readData());
        }
        mazeGame = MazeGame<T>::createMazeFromData(data);
        if (this->cache->isSolutionExist(mazeGame)) {
            cout << "cache" << endl;
            solution = this->cache->getSolution(mazeGame);
        } else {
            solution = this->solver->solve(mazeGame);
            this->cache->storeSolution(mazeGame, solution);
        }
        server->sendData(solution->StringRepresentation());
    }

    virtual ~MyTestClientHandler() {
        delete this->solver;
        delete this->cache;
    }

};
#endif
