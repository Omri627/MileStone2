#include <vector>
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"
#include "stdio.h"
template <class T>
MyTestClientHandler<T>::MyTestClientHandler(SearcherSolver<T>* solver, FileCacheManager<MazeGame<T>*, Solution*> *cache) {
    this->solver = solver;
    this->cache = cache;
}
template <class T>
MyTestClientHandler<T>::MyTestClientHandler(SearcherSolver<T>* solver) {
    this->solver = solver;
    this->cache = new FileCacheManager<MazeGame<T>*, Solution* >("cache.txt");
}
template <class T>
void MyTestClientHandler<T>::handleClient(Server * server) {
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
template <class T>
MyTestClientHandler<T>::~MyTestClientHandler() {
    delete this->solver;
    delete this->cache;
}