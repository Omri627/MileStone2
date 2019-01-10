#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include "SearcherSolution.h"
#include "Searcher.h"
template <class T>
class Dfs : public Searcher<T> {
private:
    void initializeSinglePair(Searchable<T>* searchable) {
        searchable->getInitialState().setCost(0);
    }

    void dfsVisit(State<T> state, Searchable<T>* searchable) {
        static int t = 0;
        state.setColor(GRAY);
        list < State<T>> neighbors = searchable->getAllPossibleState(state);
        for (State<T> neighbor : neighbors) {
            if (neighbor == searchable->getGoalState()) {
                neighbor.setCameFrom(&state);
                break;
            }
            if (neighbor.getColor() == WHITE) {
                dfsVisit(neighbor, searchable);
                neighbor.setCameFrom(&state);
            }
        }
        state.setColor(BLACK);
        state.setCost(t);
        t = t + 1;
    }
public:
    Dfs() {

    }

    virtual Solution* search(Searchable<T>* searchable) {
        int cost, sum;
        dfsVisit(searchable->getInitialState(), searchable);
        cost = this->getCostOfPath(searchable->getInitialState(), searchable.getGoalState());
        sum = this->getLengthOfPath(searchable->getInitialState(), searchable.getGoalState());
        return new SearcherSolution(cost, sum);
    }

};



#endif