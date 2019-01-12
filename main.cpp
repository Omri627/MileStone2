#include <iostream>
#include "Server.h"
#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "Solver.h"
#include "SearcherSolver.h"
#include "Dfs.h"
#include "BestFirstSearch.h"
#include "Astar.h"
#include "SearcherSolution.h"
#include "Bfs.h"
#include <chrono>
#include "RandomizerMaze.h"
using namespace std::chrono;

int main() {
    vector<MazeGame<int>*> mazeList1;
    vector<MazeGame<int>*> mazeList2;
    vector<MazeGame<int>*> mazeList3;
    vector<MazeGame<int>*> mazeList4;
    ifstream file("graphs.txt");
    int numOfMatrix;
    file >> numOfMatrix;
    for (int i = 0; i < numOfMatrix ; ++i) {
        vector<string> data = RandomizerMaze::readMatrix(file);
        mazeList1.push_back(new MazeGame<int>(data));
        mazeList2.push_back(new MazeGame<int>(data));
        mazeList3.push_back(new MazeGame<int>(data));
        mazeList4.push_back(new MazeGame<int>(data));
    }
    file.close();


   /* ofstream file;
    file.open("graphs.txt");
    file << "10" << endl;

    RandomizerMaze randomizer(50,-1,10);
    vector<MazeGame<int>*> mazeList;
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    mazeList.push_back(randomizer.getRandomMaze());
    MazeGame<int>* mazeGame1= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame2= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame3= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame4= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame5= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame6= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame7= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame8= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame9= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame10= randomizer.getRandomMaze();
    for(MazeGame<int>* mazeGame : mazeList) {
       file << *mazeGame;

    }
    file.close();*/

    for (int i = 0; i < numOfMatrix ; ++i) {
        BestFirstSearch<int>* bestfs = new BestFirstSearch<int>();
        SearcherSolution* s1 = bestfs->search(mazeList1[i]);
        cout << s1->getTotalCost() << "," << s1->getDevelopStates() << endl;
        delete s1;

         Dfs<int>* dfs = new Dfs<int>();
         SearcherSolution* s2 = dfs->search(mazeList4[i]);
        cout << s2->getTotalCost() << "," << s2->getDevelopStates() << endl;
         delete s2;

        Bfs<int>* bfs = new Bfs<int>();
        SearcherSolution* s3 = bfs->search(mazeList3[i]);
        cout << s3->getTotalCost() << "," << s3->getDevelopStates() << endl;
        delete s3;

        Astar<int>* aStar = new Astar<int>();
        SearcherSolution* s4 = aStar->search(mazeList2[i]);
        cout << s4->getTotalCost() << "," << s4->getDevelopStates() << endl;
        delete s4;
    }


        //high_resolution_clock::time_point t1 = high_resolution_clock::now();

        //high_resolution_clock::time_point t2 = high_resolution_clock::now();
       // auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        //cout << duration << endl;
}


