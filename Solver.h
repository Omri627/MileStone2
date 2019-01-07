#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

#include "CacheManager.h"
template <class Problem, class Solution>
class Solver {
    Problem problem;
    Solution solution;
public:
    Solver(Problem problem, Solution solution) : problem(problem), solution(solution) {}

    virtual Solution solve(Problem problem) = 0;
};


#endif //PROJECT2_SOLVER_H
