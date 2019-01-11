#ifndef FILE_CACHE_MANAGER
    #define FILE_CACHE_MANAGER

#include <string>
#include <fstream>
#include "CacheManager.h"
using namespace std;

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    map<Problem, Solution> solutions;

    string fileUrl;

    typename map<Problem, Solution>::iterator getStartIterator() {
        return this->solutions.begin();
    }

    typename map<Problem, Solution>::iterator getEndIterator() {
        return this->solutions.end();
    }

    void loadMap () {
        Problem problem;                // stored problem
        Solution solution;                // stored solution
        string delimiter;               // delimiter buffer
        ifstream file;                  // input stream of file

        /* open data file */
        file.open(this->fileUrl);
        if (!file)
            return;

        /* load instances of problem one by one and store in cache object */
        while (!file.eof()) {
            file >> problem;            // load specific problem
            file >> delimiter;          // ignore delimiter between problem and solution
            file >> solution;           // load solution for problem
            this->storeSolution(problem, solution);
        }
    }

    void saveData() {
        ofstream file;
        file.open(this->fileUrl);
        typename map < Problem, Solution >::iterator iterator;
        iterator = this->getStartIterator();
        while (iterator != this->getEndIterator()) {
            file << *iterator->first << "$" << endl << iterator->second << endl;
            iterator++;
        }
        file.close();
    }

public:
    FileCacheManager(string fileUrl) {
        this->fileUrl = fileUrl;
        this->loadMap();
    }

    virtual bool isSolutionExist(Problem problem) {
        if (this->solutions.find(problem) == this->getEndIterator())
            return false;
        return true;
    }

    virtual Solution getSolution(Problem problem) {
        return this->solutions[problem];
    }

    virtual void storeSolution(Problem problem, Solution solution) {
        this->solutions[problem] = solution;
    }

    virtual ~FileCacheManager() {
        this->saveData();
    }

};
#endif
