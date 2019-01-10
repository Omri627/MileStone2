
#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "MyPriorityQueue.h"
using namespace std;

template <class T>
class BestFirstSearch :public Searcher<T>{
private:
    MyPriorityQueue<State<T>> priorityQueue;

public:
    Solution* search(Searchable<State<T>> searchable);
};


#endif