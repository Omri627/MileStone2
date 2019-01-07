#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(StringReverserSolver* solver, CacheManager<string, string> *cache) {
    this->solver = solver;
    this->cache = cache;
}
void MyTestClientHandler::handleClient(string problem, Server * server) {
    string solution;
    if (this->cache->isSolutionExist(problem))
        solution = this->cache->getSolution(problem);
    else
        solution = this->solver->solve(problem);
    server->sendData(solution);
}