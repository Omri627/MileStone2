#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

#include "CacheManager.h"
template <class Problem, class Solution>
class Solver {
public:
    virtual Solution solve(Problem problem) = 0;
};
#endif