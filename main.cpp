#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"
#include "BestFirstSearch.h"
#include "SearcherSolution.h"
#include "MyPriorityQueue.h"

int main() {
    SerialServer* server = new SerialServer("127.0.0.1");
    FileCacheManager< string, string >* fileCacheManager = new FileCacheManager<string, string>("cache.txt");
    vector<string> data;
    string row1 = "0,0";
    string row2 = "2,2";
    string row3 = "1,0,1";
    string row4 = "1,2,1";
    string row5 = "-1,5,1";
    data.push_back(row1);
    data.push_back(row2);
    data.push_back(row3);
    data.push_back(row4);
    data.push_back(row5);
    MazeGame<int>* mazeGame = new MazeGame<int>(data);
    //Dfs<int>* dfs = new Dfs<int>();
    //Solution* s = dfs->search(mazeGame);
    //cout << s->StringRepresentation() << endl;
    MyPriorityQueue<int> q;
    int costs[] = {3,1,8,9,0};
    for (int i = 0; i < 5; i++) {
        State<int>* state = new State<int>(i);
        state->setCost(costs[i]);
        q.push(state);
    }
    while (!q.empty()) {
        cout << q.top()->getCost() << endl;
        q.pop();
    }
    delete server;
    delete mazeGame;
    //delete s;
}