#ifndef PROJECT2_MAZEGAME_H
#define PROJECT2_MAZEGAME_H

#include <map>
#include <ostream>
#include <iostream>
#include <vector>
#include "State.h"
#include "Searchable.h"

template <class T>
class MazeGame : public Searchable<T> {
private:
    typedef vector<vector<State<T>>> matrix;
    int matrixSize;
    matrix states;
    State<T> initialState;
    State<T> goalState;


public:
    MazeGame(matrix states, State<T> initialState, State<T> goalState);

    MazeGame(matrix states, struct position initial, struct position goal);

    MazeGame(vector<string> data, int matrixSize);

    virtual State<T> getInitialState();

    virtual State<T> getGoalState();

    virtual State<T> getState(position position);

    virtual bool isStateExist(int row, int column);

    virtual bool isStateExist(position position);

    virtual State<T> getState(int row, int column);

    virtual list <State<T>> getAllPossibleState(State<T> state);

    void createMazeFromData(vector<string> data) {
        /*position initialPosition;
        position goalPosition;
        const char* buffer;
        T weight;
        State<T>* state;
        char delimiter;
        for (int i = 2, j = 0; i < data.size() + 2; i++) {
            istringstream rowStream(data[i]);
            j = 0;
            while (rowStream >> weight) {
                state = new State<T>(weight, i , j);
                this->states[i][j] = *state;
                rowStream >> delimiter;
                j++;
            }
        }
        buffer = data[0].c_str();
        sscanf(buffer, "%d,%d", &initialPosition.row, &initialPosition.column);
        buffer = data[1].c_str();
        sscanf(buffer, "%d,%d", &goalPosition.row, &goalPosition.column);
        this->initialState = this->getState(initialPosition);
        this->goalState = this->getState(goalPosition); */
    }

};


#endif