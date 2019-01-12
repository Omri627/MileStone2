
#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "StatePriorityQueue.h"
#include "SearcherSolution.h"
#include "vector"
#include "CmpStatePtrs.h"

using namespace std;

template <class T>
class BestFirstSearch : public Searcher<T> {
private:
    StatePriorityQueue<State<T>*> priorityQueue;

public:
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        double newPath = 0;
        double oldPath = -1;
        priorityQueue.emplace(searchable->getInitialState());
        searchable->getInitialState()->setColor(BLACK); //initial state should be black

        while (!priorityQueue.empty()) {
            State<T>* n = priorityQueue.top();
            priorityQueue.remove(n);
            n->setColor(BLACK); //color is black so we won't check n again
            if (n == searchable->getGoalState()) {
                double sum = this->getCostOfPath(searchable->getInitialState(), n);
                double length = this->getLengthOfPath(searchable->getInitialState(), n);
                string direction = this->getDirection(searchable->getInitialState(), n);
                if (sum != -1 && length != -1) {
                    return new SearcherSolution(sum, length, 0, direction);
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
                        s->setCost(this->getCostOfPath(searchable->getInitialState(), s));
                        removeAndEmplace(s);
                    } else {
                        if (s->getCost() < oldPath || oldPath == -1) { //old path will be -1 only at the beginning
                            if (s->getColor() != GRAY) {
                                //if s is not in pq add to pq
                                removeAndEmplace(s);
                                oldPath = s->getCost();
                            } else {
                                removeAndEmplace(s);
                            }
                        }
                    }
                }
            }
        }
        return new SearcherSolution(-1, -1);
    }

private:

    void removeAndEmplace(State<T>* s) {
        priorityQueue.remove(s);
        priorityQueue.emplace(s);
    }
};




#endif