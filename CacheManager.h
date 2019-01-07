#ifndef PROJECT2_CACHEMANAGER_H
    #define PROJECT2_CACHEMANAGER_H

#include <map>
#include <iterator>

using namespace std;
template <class Problem, class Solution>
class CacheManager {
private:
    map<Problem, Solution> solutions;
protected:
    typename map<Problem, Solution>::iterator getStartIterator();

    typename map<Problem, Solution>::iterator getEndIterator();

public:
    virtual bool isSolutionExist(Problem problem);

    virtual Solution getSolution(Problem problem);

    virtual void storeSolution(Problem p, Solution s);
};

#endif