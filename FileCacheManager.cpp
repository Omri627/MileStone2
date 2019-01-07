#include <fstream>
#include <iostream>
#include "FileCacheManager.h"
template <class Problem, class Solution>
FileCacheManager<Problem, Solution>::FileCacheManager(string fileUrl) {
    this->fileUrl = fileUrl;
}

template <class Problem, class Solution>
void FileCacheManager<Problem, Solution>::loadMap() {
    Problem problem;            // problem
    Solution solution;          // solution
    ifstream file;              // input stream
    file.open(this->fileUrl);
    if (!file) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    file.ignore('$');
    while (file >> problem >> solution) {
        this->storeSolution(problem, solution);
    }
}
template <class Problem, class Solution>
void FileCacheManager<Problem, Solution>::saveData() {
    ofstream file;
    file.open(this->fileUrl, "w");
    typename map < Problem, Solution >::iterator iterator;
    iterator = this->getMapIterator();
    while (iterator != this->getEndIterator()) {
        file << iterator->first << "$" << iterator->second << endl;
        iterator++;
    }
}

