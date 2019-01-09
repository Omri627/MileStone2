
#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "queue"
using namespace std;

template <class Solution, class T>
class BestFirstSearch :public Searcher<Solution, T>{
private:
    priority_queue<State<T>> priorityQueue;
public:
    Solution search(Searchable<State<T>> searchable);
};


#endif