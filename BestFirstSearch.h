
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

public:
    /**
     * return best path on graph with Best First Search algorithm
     * @param searchable
     * @return SearcherSolution
     */
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        StatePriorityQueue<State<T>*> priorityQueue;
        double newPath = 0;
        double oldPath = -1;
        priorityQueue.push(searchable->getInitialState());
        searchable->getInitialState()->setColor(BLACK); //initial state should be black

        while (!priorityQueue.empty()) {
            State<T>* n = priorityQueue.top();
            priorityQueue.remove(n);
            n->setColor(BLACK);             //color is black so we won't check n again
            if (n == searchable->getGoalState()) {
                //update result
                double sum = this->getCostOfPath(searchable->getInitialState(), n);
                double length = this->getLengthOfPath(searchable->getInitialState(), n);
                int develops = this->getDevelopStates(searchable->getAllStates());
                string direction = this->getDirection(searchable->getInitialState(), n);
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
                        s->setCost(this->getCostOfPath(searchable->getInitialState(), s));
                        removeAndEmplace(s, &priorityQueue);
                    } else {
                        if (s->getCost() < oldPath || oldPath == -1) { //old path will be -1 only at the beginning
                            if (s->getColor() != GRAY) {
                                //if s is not in pq add to pq
                                removeAndEmplace(s, &priorityQueue);
                                oldPath = s->getCost();
                            } else {
                                removeAndEmplace(s,&priorityQueue);
                            }
                        }
                    }
                }
            }
        }
        //no path found
        return new SearcherSolution(-1, -1);
    }

private:
    /**
     * remove amd emplace states from the queue
     * @param pair of state and double
     * @param pq priority queue
     */
    void removeAndEmplace(State<T>* s, StatePriorityQueue<State<T>*>* priorityQueue) {
        priorityQueue->remove(s);
        priorityQueue->push(s);
    }
};




#endif