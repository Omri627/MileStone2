#ifndef FILE_CACHE_MANAGER
    #define FILE_CACHE_MANAGER

#include <string>
#include "CacheManager.h"
using namespace std;

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    map<Problem, Solution> solutions;

    string fileUrl;

    typename map<Problem, Solution>::iterator getStartIterator();

    typename map<Problem, Solution>::iterator getEndIterator();

    void loadMap();

    void saveData();

public:
    FileCacheManager(string fileUrl);

    virtual bool isSolutionExist(Problem problem);

    virtual Solution getSolution(Problem problem);

    virtual void storeSolution(Problem problem, Solution solution);

    virtual ~FileCacheManager();

};
#endif