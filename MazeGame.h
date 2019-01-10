#ifndef PROJECT2_MAZEGAME_H
#define PROJECT2_MAZEGAME_H

#include <map>
#include "State.h"
#include "Searchable.h"
#include <vector>
#include <sstream>

template <class T>
class MazeGame : public Searchable<T> {
private:
    typedef vector<vector<State<T>*>> matrix;
    int matrixSize;
    matrix statesMatrix;
    State<T>* initialState;
    State<T>* goalState;

public:
    MazeGame(matrix states, State<T>* initialState, State<T>* goalState, int matrixSize){
        this->statesMatrix = states;
        this->initialState = initialState;
        this->goalState = goalState;
        this->matrixSize = matrixSize;
    }

    MazeGame(matrix states, struct position initial, struct position goal, int matrixSize){
        this->states = states;
        this->initialState = getState(initial);
        this->goalState = getState(goal);
        this->matrixSize = matrixSize;
    }

    virtual State<T> getInitialState(){
        return this->initialState;
    }

    virtual State<T> getGoalState() {
        return this->goalState;
    }

    virtual State<T> getState(position position) {
        return this->states[position.row][position.column];
    }

    virtual bool isStateExist(position position) {
        if (position.row > this->matrixSize || position.row < 0
                || position.column > this->matrixSize || position.column < 0)
            return false;
        return true;
    }

    virtual State<T> getState(int row, int column){
        this->statesMatrix[row][column];
    }

    virtual list <State<T>> getAllPossibleState(State<T> state) {
        list < State<T> > neighbors;
        if (this->isStateExist(state.getRow() - 1, state.getColumn()))
            neighbors.insert(this->getState(state.getRow() - 1, state.getColumn()));
        if (this->isStateExist(state.getRow(), state.getColumn() - 1))
            neighbors.insert(this->getState(state.getRow(), state.getColumn() - 1));
        if (this->isStateExist(state.getRow() + 1, state.getColumn()))
            neighbors.insert(this->getState(state.getRow() + 1, state.getColumn()));
        if (this->isStateExist(state.getRow(), state.getColumn() + 1))
            neighbors.insert(this->getState(state.getRow(), state.getColumn() + 1));
        return neighbors;
    }

    static MazeGame *createMazeFromData(vector<string> data) {
        position initialPosition;
        position goalPosition;
        matrix matrixStates;
        const char* buffer;
        T weight;
        State<T>* state;
        char delimiter;
        for (int i = 0, j = 0; i < data.size() - 2; i++) {
            istringstream rowStream(data[i]);
            j = 0;
            while (rowStream >> weight) {
                state = new State<T>(weight, i, j);
                matrixStates[i][j] = state;
                rowStream >> delimiter;
                j++;
            }
        }
        buffer = data[0].c_str();
        sscanf(buffer, "%d,%d", &initialPosition.row, &initialPosition.column);
        buffer = data[1].c_str();
        sscanf(buffer, "%d,%d", &goalPosition.row, &goalPosition.column);
        return new MazeGame(matrixStates, initialPosition, goalPosition);
    }

    virtual matrix getStates(){
        return this->states;
    }
};



#endif