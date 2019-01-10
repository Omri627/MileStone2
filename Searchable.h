
#ifndef PROJECT2_SEARCHABLE_H
#define PROJECT2_SEARCHABLE_H

#include <list>
#include <map>
#include "State.h"
struct position {
    int row;
    int column;
};
typedef struct position position;
using namespace std;
template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() = 0;

    virtual State<T> getGoalState() = 0;

    virtual list<State<T>> getAllPossibleState(State<T> s) = 0;
    //todo: I think it is need to be with *

    //virtual list<State<T>*> getNeighbors(State<T> state);
};

#endif //PROJECT2_SEARCHABLE_H
