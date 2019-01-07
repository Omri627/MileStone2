#include "CacheManager.h"
template <class Problem, class Solution>
bool CacheManager<Problem, Solution>::isSolutionExist(Problem problem) {
    if (this->solutions.find(problem) == this->solutions.end())
        return false;
    return true;
}
template <class Problem, class Solution>
Solution CacheManager<Problem, Solution>::getSolution(Problem problem) {
    return this->solutions[problem];
}

template <class Problem, class Solution>
void CacheManager<Problem, Solution>::storeSolution(Problem problem, Solution solution) {
    if (problem == NULL || solution == NULL)
        return;
    this->solutions[problem] = solution;
}
template <class Problem, class Solution>
typename map <Problem, Solution>::iterator CacheManager<Problem, Solution>::getStartIterator() {
    return this->solutions.begin();
}
template <class Problem, class Solution>
typename map <Problem, Solution>::iterator CacheManager<Problem, Solution>::getEndIterator() {
    return this->solutions.end();
}