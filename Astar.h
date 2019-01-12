#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include "Searcher.h"
#include "SearcherSolution.h"
#include "PairPriorityQueue.h"

using namespace std;

template <class T>
class Astar : public Searcher<T> {
private:
    PairPriorityQueue<State<T>*,double> priorityQueue;

public:
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        State<T>* initialState = searchable->getInitialState();
        double oldPath = -1;
        priorityQueue.emplace(make_pair(initialState, 0));
        initialState->setColor(BLACK); //initial state should be black

        while (!priorityQueue.empty()) {
            State<T>* n = priorityQueue.top().first;
            priorityQueue.remove(make_pair(n,getManhDist(initialState,n)));
            n->setColor(BLACK); //color is black so we won't check n again
            if (n == searchable->getGoalState()) {
                double sum = this->getCostOfPath(initialState, n);
                double length = this->getLengthOfPath(initialState, n);
                int develops = this->getDevelopStates(searchable->getAllStates());
                string direction = this->getDirection(initialState, n);
                if (sum != -1 && length != -1) {
                    return new SearcherSolution(sum, length, develops, direction);
                }
                return new SearcherSolution(-1, -1);
            }

            list<State<T>*> neighbors = searchable->getAllPossibleState(n); //all n neighbors
            for (State<T>* s : neighbors) {
                if (s->getColor() != BLACK) {
                    if ((s->getColor() != BLACK) && (s->getColor() != GRAY)) {
                        s->setCameFrom(n);
                        s->setColor(GRAY); //color is gray because we add it to queue
                        // update the sum of the path from the start to s
                        s->setCost(this->getCostOfPath(initialState, s));
                        removeAndEmplace(make_pair(s,getManhDist(initialState, s)));
                    } else {
                        if (s->getCost() + getManhDist(initialState ,s) < oldPath || oldPath == -1) { //old path will be -1 only at the beginning
                            if (s->getColor() != GRAY) {
                                //if s is not in pq add to pq
                                removeAndEmplace(make_pair(s,getManhDist(initialState, s)));
                                oldPath = s->getCost() + getManhDist(initialState ,s);
                            } else {
                                removeAndEmplace(make_pair(s,getManhDist(initialState, s)));
                            }
                        }
                    }
                }
            }
        }
        return new SearcherSolution(-1, -1);
    }

private:
    double getManhDist(State<T>* start, State<T>* end) {
        int x = abs(start->getRow() - end->getRow());
        int y = abs(start->getColumn() - end->getColumn());
        return sqrt(x+y);
    }

    void removeAndEmplace(pair<State<T>*,double> pair) {
        priorityQueue.remove(pair);
        priorityQueue.emplace(pair);
    }
};
#endif //PROJECT2_ASTAR_H
