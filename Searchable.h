
#ifndef PROJECT2_SEARCHABLE_H
#define PROJECT2_SEARCHABLE_H

#include <list>
#include "State.h"
using namespace std;
template <class T>
class Searchable {
private:
    virtual State<T> getInitialState() = 0;

    virtual State<T> getGoalState();

    list<State<T>> getAllPossibleState(State<T> s);
};


#endif //PROJECT2_SEARCHABLE_H
