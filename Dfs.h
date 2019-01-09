#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#import "Searcher.h"
template <class T>
class Dfs : public Searcher<T> {
private:
    void initializeSinglePair(Searchable<State<T>> searchable);

    void dfsVisit(State<T> state, Searchable<State<T>> searchable);

public:
    virtual Solution* search(Searchable<State<T>> searchable);

};

#endif //PROJECT2_DFS_H
