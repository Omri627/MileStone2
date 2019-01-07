
#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H

#include "Searchable.h"

template <class Solution, class State>
class Searcher {
public:
    virtual Solution search(Searchable<State> searchable) = 0;
};


#endif //PROJECT2_SEARCHER_H
