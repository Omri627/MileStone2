
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
/* searchable objects are structure contains elements(=nodes) the can be searched.
 * by given two node denoted as initial and goal, searcher algorithms can compute the
 * shortest path between them*/
template <class T>
class Searchable {
public:
    /**
     * get the initial state to start the search from.
     * @return returns the initial state
     */
    virtual State<T>* getInitialState() const = 0;
    /**
     * get the goal state that searcher algorithms should find a path to this node,
     * @return returns the goal state
     */
    virtual State<T>* getGoalState() const = 0;
    /**
     * getAllPossibleState method gets specific state.
     * and returns list of neighbors of given state.
     * @param s state object
     * @return returns list of neighbors of given state.
     */
    virtual list<State<T>*> getAllPossibleState(State<T>* s) = 0;
    /**
     * creates a list of all states in graph.
     * @return returns a list of all states in graph.
     */
    virtual list<State<T>*> getAllStates() const = 0;
};

#endif