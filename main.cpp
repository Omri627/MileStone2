#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"

int main() {
    SerialServer *server = new SerialServer("127.0.0.1");
    Dfs<int>* dfs = new Dfs<int>();
    SearcherSolver<int>* searcher = new SearcherSolver<int>(dfs);
    MyTestClientHandler<int> *handler = new MyTestClientHandler<int>(searcher);
    server->open(5400, handler);
    delete server;
}