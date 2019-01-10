#ifndef BREADTH_FIRST_SEARCH
    #define BREADTH_FIRST_SEARCH

#include "MyPriorityQueue.h"
#include "Searcher.h"
template <class T>
class Bfs : Searcher<T> {
private:
    void initialize(Searchable<T>* searchable, MyPriorityQueue<State<T>>) {
        searchable->getInitialState()->setCost(0);
        searchable->getInitialState()->setColor(GRAY);

    }
public:
    virtual Solution *search(Searchable<T> *searchable) {
        MyPriorityQueue<State<T >> priorityQueue;


    }

};
/*
BFS(G = (V, E), s)
1 for each u ∈ V
2 d[u] ← ∞
3 π[u] ← NULL
4 color[u] ← w
5 d[s] ← 0
6 color[s] ← g
7 Q.Enqueue(s)
8 while |Q| 6= ∅
9 u ← Q.Dequeue()
10 for each v ∈ ADJ[u]
11 if color[v] = w
12 color[v] ← g
13 d[v] ← d[u] + 1
14 Q.Enqueue(v)
15 color[u] ← b
*/
#endif //PROJECT2_BREADTHFIRSTSEARCH_H
