#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"

int main() {
    SerialServer* server = new SerialServer("127.0.0.1");
    FileCacheManager< string, string >* fileCacheManager = new FileCacheManager<string, string>("cache.txt");
    vector<string> data;
    string row1 = "0,0";
    string row2 = "3,3";
    string row3 = "1,2,2,2";
    string row4 = "1,2,2,2";
    string row5 = "1,2,2,2";
    string row6 = "1,1,1,1";
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    data.push_back(row5);
    data.push_back(row6);
    MazeGame<int>* mazeGame = new MazeGame<int>(data);

    delete server;
}