#ifndef FILE_CACHE_MANAGER
    #define FILE_CACHE_MANAGER

#include <string>
#include <fstream>
#include "CmpMazeGame.h"
#include "CacheManager.h"
pthread_mutex_t global_mutex;
using namespace std;

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    map<Problem, Solution, CmpMazeGame<Problem> > solutions;
    string fileUrl;
    //todo: change file name

    typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator getStartIterator() {
        return this->solutions.begin();
    }

    typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator getEndIterator() {
        return this->solutions.end();
    }

    void loadMap () {
        Problem problem;                // stored problem
        Solution solution;                // stored solution
        string delimiter;               // delimiter buffer
        ifstream file;                  // input stream of file
        char newline;
        /* open data file */
        file.open(this->fileUrl);
        if (!file)
            return;
        pthread_mutex_lock(&global_mutex);
        /* load instances of problem one by one and store in cache object */
        while (file >> &problem) {
            file >> delimiter;          // ignore delimiter between problem and solution
            file >> &solution;           // load solution for problem
            this->storeSolution(problem, solution);
        }
        pthread_mutex_unlock(&global_mutex);

    }

    void saveData() {
        ofstream file;
        file.open(this->fileUrl);
        typename map < Problem, Solution, CmpMazeGame<Problem> >::iterator iterator;
        iterator = this->solutions.begin();
        pthread_mutex_lock(&global_mutex);
        while (iterator != this->solutions.end()) {
            file << *iterator->first << "$" << endl << iterator->second;
            iterator++;
        }
        pthread_mutex_unlock(&global_mutex);
        file.close();
    }

public:
    FileCacheManager(string fileUrl) {
        this->fileUrl = fileUrl;
        this->loadMap();
    }

    virtual bool isSolutionExist(const Problem problem) {
        typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator iterator;
        iterator = this->solutions.find(problem);
        if (iterator == this->solutions.end())
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
        typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator it;
        for (it = this->solutions.begin(); it != this->solutions.end() ; it++) {
            if (it->first != nullptr) {
                delete it->first;
            }
            if (it->second != nullptr) {
                delete it->second;
            }
        }
    }



};
#endif
