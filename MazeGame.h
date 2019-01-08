#ifndef PROJECT2_MAZEGAME_H
#define PROJECT2_MAZEGAME_H

#include <map>
#include "State.h"
#include "Searchable.h"

template <class T>
class MazeGame : public Searchable<T> {
private:
    map<position, State<T> > states;
    State<T> initialState;
    State<T> goalState;

public:
    MazeGame(map<position, State<T> > states, State<T> initialState, State<T> goalState);

    MazeGame(map<position, State<T> > states, struct position initial, struct position goal);

    virtual State<T> getInitialState();

    virtual State<T> getGoalState();

    virtual State<T> getState(position position);

    virtual bool isStateExist(position position);

    virtual State<T> getState(int row, int column);

    virtual list <State<T>> getAllPossibleState(State<T> state);

    static MazeGame *createMazeFromData(vector<string> data);

    virtual map<position, State<T>> getStates();
};



#endif