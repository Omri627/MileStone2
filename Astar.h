#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include "Searcher.h"
#include "SearcherSolution.h"
#include "PairPriorityQueue.h"

template <class T>
class Astar : public Searcher<T> {

public:
    /**
     * return best path on graph with a* algorithm
     * @param searchable
     * @return SearcherSolution
     */
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        PairPriorityQueue<State<T>*,double> pq;
        State<T>* initialState = searchable->getInitialState();
        double oldPath = -1;
        pq.push(make_pair(initialState, 0));
        initialState->setColor(BLACK); //initial state should be black

        while (!pq.empty()) {
            State<T>* n = pq.top().first;
            pq.remove(make_pair(n,getManhDist(initialState,n)));
            n->setColor(BLACK); //color is black so we won't check n again
            if (n == searchable->getGoalState()) {
                //update result
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
                        removeAndEmplace(make_pair(s,getManhDist(initialState, s)),&pq);
                    } else {
                        if (s->getCost() + getManhDist(initialState ,s) < oldPath || oldPath == -1) { //old path will be -1 only at the beginning
                            if (s->getColor() != GRAY) {
                                //if s is not in pq add to pq
                                removeAndEmplace(make_pair(s,getManhDist(initialState, s)), &pq);
                                oldPath = s->getCost() + getManhDist(initialState ,s);
                            } else {
                                removeAndEmplace(make_pair(s,getManhDist(initialState, s)),&pq);
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
     * thefunction is the the arieal distance between two state
     * @param start state
     * @param end state
     * @return the distance
     */
    double getManhDist(State<T>* start, State<T>* end) {
        int x = abs(start->getRow() - end->getRow());
        int y = abs(start->getColumn() - end->getColumn());
        return sqrt(x+y);
    }
    /**
     * remove amd emplace states from the queue
     * @param pair of state and double
     * @param pq priority queue
     */
    void removeAndEmplace(pair<State<T>*,double> pair, PairPriorityQueue<State<T>*,double>* pq) {
        pq->remove(pair);
        pq->push(pair);
    }
};
#endif //PROJECT2_ASTAR_H
