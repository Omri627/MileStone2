#include <fstream>
#include "FileCacheManager.h"
template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::FileCacheManager(string fileUrl) {
    this->fileUrl = fileUrl;
    this->loadMap();
}
template <class Problem, class Solution>
typename map <Problem, Solution>::iterator FileCacheManager<Problem, Solution>::getStartIterator() {
    return this->solutions.begin();
}
template <class Problem, class Solution>
typename map <Problem, Solution>::iterator FileCacheManager<Problem, Solution>::getEndIterator() {
    return this->solutions.end();
}
template <class Problem, class Solution>
void FileCacheManager<Problem, Solution>::loadMap() {
    Problem problem;            // problem
    Solution solution;          // solution
    string dd;
    ifstream file;              // input stream
    file.open(this->fileUrl);
    if (!file) {
        return;
        // cerr << "Unable to open file";
        //exit(1);   // call system to stop
    }
    while (file >> problem) {
        file >> solution;
        file >> solution;
        this->storeSolution(problem, solution);
    }
}
template <class Problem, class Solution>
void FileCacheManager<Problem, Solution>::saveData() {
    ofstream file;
    file.open(this->fileUrl);
    typename map < Problem, Solution >::iterator iterator;
    iterator = this->getStartIterator();
    while (iterator != this->getEndIterator()) {
        file << iterator->first << endl << "$" << endl << iterator->second << endl;
        iterator++;
    }
    file.close();
}
template<class Problem, class Solution>
bool FileCacheManager<Problem, Solution>::isSolutionExist(Problem problem) {
    if (this->solutions.find(problem) == this->getEndIterator())
        return false;
    return true;
}

template<class Problem, class Solution>
Solution FileCacheManager<Problem, Solution>::getSolution(Problem problem) {
    return this->solutions[problem];
}

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::storeSolution(Problem problem, Solution solution) {
    this->solutions[problem] = solution;
}

template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::~FileCacheManager() {
    this->saveData();
}
