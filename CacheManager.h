#ifndef PROJECT2_CACHEMANAGER_H
    #define PROJECT2_CACHEMANAGER_H

#include <map>
#include <iterator>
#include "MazeGame.h"
#include "SearcherSolution.h"

using namespace std;
template <class Problem, class Solution>
class CacheManager {
public:
    /**
    * isSolutionExist method checks whether there is solution stored in chache
    * for given problem
    * @param problem specific problem
    * @return returns true if problem already solved and his solution stored in memory
    * at any other case returns false
    */
    virtual bool isSolutionExist(Problem problem) = 0;
    /**
     * getSolution method gets a problem and returns his value.
     * assumption: the problem's solution stored in chache.
     * @param problem specific problem.
     * @return returns the solution for given instance of problem,
     */
    virtual Solution getSolution(Problem problem) = 0;
    /**
     * storeSolution method gets a problem and solution.
     * and stored them in cache.
     * @param problem instance of problem
     * @param solution solution for this problem
     */
    virtual void storeSolution(Problem problem, Solution solution) = 0;
};

#endif