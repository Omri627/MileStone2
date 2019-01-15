#include "Server.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Astar.h"
#include "SearcherSolution.h"

int main(int args, char* argv[]) {
    if (args > 1) {
        ParallelServer* server = new ParallelServer(20);
        Searcher<int>* as = new Astar<int>();
        SearcherSolver<int>* solver = new SearcherSolver<int>(as);
        MyTestClientHandler<int>* handler = new MyTestClientHandler<int>(solver);
        server->open(stoi(argv[1]),handler);
        delete server;
        delete as;
        if (solver != nullptr)
            delete solver;
        return 0;
    }
}