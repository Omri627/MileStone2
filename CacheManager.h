#ifndef PROJECT2_CACHEMANAGER_H
    #define PROJECT2_CACHEMANAGER_H

#include <map>
#include <iterator>

using namespace std;
template <class Problem, class Solution>
class CacheManager {
public:
    virtual bool isSolutionExist(Problem problem) = 0;

    virtual Solution getSolution(Problem problem) = 0;

    virtual void storeSolution(Problem p, Solution s) = 0;
};

#endif