
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
    virtual State<T>* getInitialState() const = 0;

    virtual State<T>* getGoalState() const = 0;

    virtual list<State<T>*> getAllPossibleState(State<T>* s) = 0;
};

#endif //PROJECT2_SEARCHABLE_H
