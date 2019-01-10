#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include "SearcherSolution.h"
#include "Searcher.h"
template <class T>
class Dfs : public Searcher<T> {
private:
    void initialize(Searchable<T>* searchable) {
        searchable->getInitialState()->setCost(0);
        searchable->getInitialState()->setColor(GRAY);
    }
    void dfsVisit(State<T>* state, Searchable<T>* searchable) {
        state->setColor(GRAY);
        list < State<T> *> neighbors = searchable->getAllPossibleState(state);
        for (State<T>* neighbor : neighbors) {
            relax(state, neighbor);
            if (neighbor->getColor() == WHITE) {
                dfsVisit(neighbor, searchable);
                neighbor->setCameFrom(state);
            }
        }
        state->setColor(BLACK);
    }
public:
    Dfs() {

    }

    virtual Solution* search(Searchable<T>* searchable) {
        int cost, sum;                  // cost and sum of path
        initialize(searchable);
        dfsVisit(searchable->getInitialState(), searchable);
        cost = searchable->getGoalState()->getCost();
        sum = this->getLengthOfPath(searchable->getInitialState(), searchable->getGoalState());
        return new SearcherSolution(cost, sum);
    }

    void relax(State<T>* from, State<T> * to) {
        if (to->getCost() > from->getCost() + to->getState() || to->getCost() == -1) {
            to->setCost(from->getCost() + to->getState());
            to->setCameFrom(from);
        }
    }


};


#endif