
#ifndef PROJECT2_SEARCHER_H
    #define PROJECT2_SEARCHER_H

#include "Searchable.h"
#include "vector"
#include "Solution.h"
using namespace std;
template <class T>
class Searcher {
protected:
    void relax(State<T>* from, State<T> * to) {
        if (to->getCost() > from->getCost() + to->getState() || to->getCost() == -1) {
            to->setCost(from->getCost() + to->getState());
            to->setCameFrom(from);
        }
    }
    virtual double getCostOfPath(State<T>* start, State<T>* end) {
        double sum = 0;
        State<T>* temp= end;
        while (temp != start) {
            sum += temp->getState();
            temp = temp->getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }
        }
        return sum;
    }

    virtual double getLengthOfPath(State<T>* start, State<T>* end) {
        double counter = 0;
        State<T>* temp = end;
        while (temp != start) {
            counter += 1;
            temp = temp->getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }

        }
        return counter;
    }


public:
    virtual SearcherSolution *search(Searchable<T> *searchable) = 0;




};
#endif //PROJECT2_SEARCHER_H
