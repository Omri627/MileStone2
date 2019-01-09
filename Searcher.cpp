
#include "Searcher.h"
template <class T>
double Searcher<T>::getCostOfPath(State<T> start, State<T> end) {
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

template <class T>
double Searcher<T>::getLengthOfPath(State<T> start, State<T> end) {
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

