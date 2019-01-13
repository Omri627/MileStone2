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
    /*ParallelServer* server = new ParallelServer(20);
    Searcher<int>* bfs = new Bfs<int>();
    SearcherSolver<int>* solver = new SearcherSolver<int>(bfs);
    MyTestClientHandler<int>* handler = new MyTestClientHandler<int>(solver);
    server->open(5400, handler);
    */
     string row1 = "2,3,4";
    string row2 = "5,6,7";
    string row3 = "0,0";
    string row4 = "1,2";
    vector<string> vector;
    vector.push_back(row1);
    vector.push_back(row2);
    vector.push_back(row3);
    vector.push_back(row4);
    Astar<int>* astar = new Astar<int>();
    SearcherSolution* searcherSolution = astar->search(new MazeGame<int>(vector));
    //delete server;
}
/*
 *     vector<string> data;
    string row1 = "0,0";
    string row2 = "2,2";
    string row3 = "1,0,1";
    string row4 = "1,0,1";
    string row5 = "-1,0,1";
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    data.push_back(row5);
    MazeGame<int>* mazeGame = new MazeGame<int>(data);
    Dfs<int>* dfs = new Dfs<int>();
    Solution* s = dfs->search(mazeGame);
    cout << s->StringRepresentation() << endl;
 */