
#ifndef PROJECT2_SEARCHER_H
    #define PROJECT2_SEARCHER_H

#include "Searchable.h"
#include "vector"
#include "Solution.h"
using namespace std;
template <class T>
class Searcher {
public:
    virtual Solution *search(Searchable<T> *searchable) = 0;

    virtual double getCostOfPath(State<T> start, State<T> end)  {
        double sum = 0;
        State<T> temp = end;
        while (temp != start) {
            sum += temp.getCost();
            temp = temp.getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }
        }
        return sum;
    }

    virtual double getLengthOfPath(State<T> start, State<T> end) {
        double counter = 0;
        State<T> temp = end;
        while (temp != start) {
            counter += 1;
            temp = temp.getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }

        }
        return counter;
    }


};
#endif //PROJECT2_SEARCHER_H
