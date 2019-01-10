#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"
#include "BestFirstSearch.h"
#include "SearcherSolution.h"

int main() {


    SerialServer* server = new SerialServer("127.0.0.1");
    FileCacheManager< string, string >* fileCacheManager = new FileCacheManager<string, string>("cache.txt");
    vector<string> data;
    string row1 = "0,0";
    string row2 = "3,3";
    string row3 = "1,3,3,6";
    string row4 = "5,4,2,1";
    string row5 = "3,-1,100,99";
    string row6 = "19,2,23,23";
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    data.push_back(row5);
    data.push_back(row6);
    MazeGame<int>* mazeGame = new MazeGame<int>(data);
    BestFirstSearch<int>* bfs = new BestFirstSearch<int>();
    Solution* s = bfs->search(mazeGame);
    cout << s->StringRepresentation() << endl;
    delete server;
    delete mazeGame;
    delete s;
}