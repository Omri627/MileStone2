
#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H

#include "Searchable.h"
#include "vector"
using namespace std;
template <class Solution, class T>
class Searcher {
public:
    virtual Solution search(Searchable<State<T>> searchable) = 0;

    virtual double getCostOfPath(State<T> start, State<T> end);

    virtual double getLengthOfPath(State<T> start, State<T> end);



};


#endif //PROJECT2_SEARCHER_H
