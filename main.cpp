#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"
#include "BestFirstSearch.h"
#include "SearcherSolution.h"
#include "Bfs.h"
#include "Astar.h"
int main() {
    ParallelServer* server = new ParallelServer(20);
    Searcher<int>* bfs = new Bfs<int>();
    SearcherSolver<int>* solver = new SearcherSolver<int>(bfs);
    MyTestClientHandler<int>* handler = new MyTestClientHandler<int>(solver);
    server->open(5400, handler);
    delete server;
}
