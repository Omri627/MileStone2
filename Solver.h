#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

#include "CacheManager.h"
template <class Problem, class Solution>
class Solver {
public:
    /**
     * solve method gets a specific instance of problem
     * solve the problem and returns the solution.
     * @param problem instance of problem
     * @return returns solution for given problem
     */
    virtual Solution solve(Problem problem) = 0;
};

#endif