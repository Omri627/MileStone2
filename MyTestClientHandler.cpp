#include "MyTestClientHandler.h"
#include "FileCacheManager.h"

MyTestClientHandler::MyTestClientHandler(StringReverserSolver* solver, FileCacheManager<string, string> *cache) {
    this->solver = solver;
    this->cache = cache;
}
MyTestClientHandler::MyTestClientHandler(StringReverserSolver* solver) {
    this->solver = solver;
    this->cache = new FileCacheManager<string, string>("cache.txt");
}
void MyTestClientHandler::handleClient(string problem, Server * server) {
    string solution;
    if (this->cache->isSolutionExist(problem)) {
        cout << "cache" << endl;
        solution = this->cache->getSolution(problem);
    } else {
        solution = this->solver->solve(problem);
        this->cache->storeSolution(problem, solution);
    }
    server->sendData(solution);
}
MyTestClientHandler::~MyTestClientHandler() {
    delete this->solver;
    delete this->cache;
}