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
    ofstream file;
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
    /*MazeGame<int>* mazeGame1= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame2= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame3= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame4= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame5= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame6= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame7= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame8= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame9= randomizer.getRandomMaze();
    MazeGame<int>* mazeGame10= randomizer.getRandomMaze();*/
    for(MazeGame<int>* mazeGame : mazeList) {
       file << *mazeGame;

    }
    file.close();

    for(MazeGame<int>* mazeGame : mazeList) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();


        BestFirstSearch<int>* bfs = new BestFirstSearch<int>();
        Solution* s1 = bfs->search(mazeGame);
        cout << "BestFirstSearch: " << s1->StringRepresentation() << endl;
        delete s1;

       /*  Astar<int>* aStar = new Astar<int>();
         Solution* s2 = aStar->search(mazeGame);
         cout << "A*: " << s2->StringRepresentation() << endl;
         delete s2;*/

        /* Bfs<int>* bfs = new Bfs<int>();
         Solution* s3 = bfs->search(mazeGame);
         cout << "BFS: " << s3->StringRepresentation() << endl;
         delete s3;*/

         /*Dfs<int>* dfs = new Dfs<int>();
         Solution* s4 = dfs->search(mazeGame);
         cout << "DFS: " << s4->StringRepresentation() << endl;
         delete s4;
*/
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        cout << duration << endl;
        delete mazeGame;
    }


}
