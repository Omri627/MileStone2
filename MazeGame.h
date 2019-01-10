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
    typedef vector<vector<State<T> *>> matrix;
    int matrixSize;
    matrix statesMatrix;
    State<T> *initialState;
    State<T> *goalState;

    MazeGame<T> *createMazeFromData(vector<string> data) {
        position initialPosition;
        position goalPosition;
        const char *buffer;
        T weight;
        State<T> *state;
        char delimiter;
        for (int i = 2, j = 0; i < data.size(); i++) {
            string row = data.at(i);
            istringstream rowStream(row);
            j = 0;
            while (rowStream >> weight) {
                state = new State<T>(weight, i-2, j);
                this->setState(i-2, j, state);
                rowStream >> delimiter;
                j++;
            }
        }
        buffer = data[0].c_str();
        sscanf(buffer, "%d,%d", &initialPosition.row, &initialPosition.column);
        buffer = data[1].c_str();
        sscanf(buffer, "%d,%d", &goalPosition.row, &goalPosition.column);
        this->initialState = getState(initialPosition);
        this->goalState = getState(goalPosition);
    }


public:
    MazeGame(matrix states, State<T> *initialState, State<T> *goalState, int matrixSize) {
        this->statesMatrix = states;
        this->initialState = initialState;
        this->goalState = goalState;
        this->matrixSize = matrixSize;
    }

    MazeGame(matrix states, struct position initial, struct position goal, int matrixSize) {
        this->states = states;
        this->initialState = getState(initial);
        this->goalState = getState(goal);
        this->matrixSize = matrixSize;
    }

    MazeGame(vector<string> data) {
        this->matrixSize = data.size() - 2;
        this->initMatrix();
        this->createMazeFromData(data);
    }

    virtual State<T> *getState(position position) {
        return this->statesMatrix[position.row][position.column];
    }

    virtual bool isStateExist(position position) {
        if (position.row > this->matrixSize - 1 || position.row < 0
            || position.column > this->matrixSize - 1 || position.column < 0)
            return false;
        return true;
    }

    virtual bool isStateExist(int row, int column) {
        if (row > this->matrixSize - 1 || row < 0
            || column > this->matrixSize - 1 || column < 0)
            return false;
        return true;
    }

    virtual State<T> *getState(int row, int column) {
        return this->statesMatrix[row][column];
    }

    virtual list<State<T> *> getAllPossibleState(State<T> *state) {
        list < State<T> * > neighbors;
        if (this->isStateExist(state->getRow() - 1, state->getColumn()) && state->getState() != -1)
            neighbors.push_back(this->getState(state->getRow() - 1, state->getColumn()));
        if (this->isStateExist(state->getRow(), state->getColumn() - 1) && state->getState() != -1)
            neighbors.push_back(this->getState(state->getRow(), state->getColumn() - 1));
        if (this->isStateExist(state->getRow() + 1, state->getColumn()) && state->getState() != -1)
            neighbors.push_back(this->getState(state->getRow() + 1, state->getColumn()));
        if (this->isStateExist(state->getRow(), state->getColumn() + 1) && state->getState() != -1)
            neighbors.push_back(this->getState(state->getRow(), state->getColumn() + 1));
        return neighbors;
    }

    virtual matrix getStates() {
        return this->statesMatrix;
    }

    State<T> *getInitialState() const {
        return this->initialState;
    }

    void setInitialState(State<T> *initialState) {
        this->initialState = initialState;
    }

    State<T> *getGoalState() const {
        return this->goalState;
    }

    void setGoalState(State<T> *goalState) {
        this->goalState = goalState;
    }

    void setState(int row, int column, State<T> *state) {
/*        vector<State<T> *> rowVector;
        rowVector = this->statesMatrix.at(row);
        rowVector.at(column) = state;*/
        this->statesMatrix[row][column] = state;
    }

    void initMatrix() {
        for (int i = 0; i < this->matrixSize; i++) {
            vector<State<T> *> rowVector;
            for (int j = 0; j < this->matrixSize; j++) {
                rowVector.push_back(nullptr);
            }
            this->statesMatrix.push_back(rowVector);
        }
    }

};



#endif