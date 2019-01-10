
#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "MyPriorityQueue.h"
#include "SearcherSolution.h"
#include "vector"
#include "CmpStatePtrs.h"

using namespace std;

template <class T>
class BestFirstSearch : public Searcher<T>{
private:
    MyPriorityQueue<State<T>*> priorityQueue;

public:
    virtual Solution *search(Searchable<T> *searchable) {
        double newPath = 0;
        double oldPath = -5;
        priorityQueue.emplace(searchable->getInitialState());
        searchable->getInitialState()->setColor(BLACK); //initial state should be black

        while (!priorityQueue.empty()) {
            State<T>* n = priorityQueue.top();
            priorityQueue.remove(n);
            n->setColor(BLACK); //color is black so we won't check n again
            if (n == searchable->getGoalState()) {
                double sum = this->getCostOfPath(searchable->getInitialState(), n);
                double length = this->getLengthOfPath(searchable->getInitialState(), n);
                if (sum != -1 && length != -1) {
                    return new SearcherSolution(sum, length);
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
                        priorityQueue.remove(s);
                        priorityQueue.emplace(s);
                    } else {
                        if (s->getCost() < oldPath || oldPath == -5) { //old path will be -1 only at the beginning
                            if (s->getColor() != GRAY) {
                                //if s is not in pq add to pq
                                priorityQueue.remove(s);
                                priorityQueue.emplace(s);
                                oldPath = newPath;
                            } else {
                                priorityQueue.remove(s);
                                priorityQueue.emplace(s);
                            }
                        }
                    }
                }
            }
        }
    }
};



#endif