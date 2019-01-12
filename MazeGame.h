#ifndef PROJECT2_MAZEGAME_H
#define PROJECT2_MAZEGAME_H

#include <map>
#include "State.h"
#include "Searchable.h"
#include <vector>
#include <sstream>
#include <ostream>
#include <istream>

template <class T>
class MazeGame : public Searchable<T> {
private:
    typedef vector<vector<State<T> *>> matrix;
    unsigned long matrixSize;
    matrix statesMatrix;
    State<T> *initialState;
    State<T> *goalState;

    void initMatrix() {
        for (int i = 0; i < this->matrixSize; i++) {
            vector<State<T> *> rowVector;
            for (int j = 0; j < this->matrixSize; j++) {
                rowVector.push_back(nullptr);
            }
            this->statesMatrix.push_back(rowVector);
        }
    }

    bool isValidData(vector<string> data) {
        if (!isValidMatrixRow(data[0], 1) || !isValidMatrixRow(data[1], 1))
            return false;
        for (int i = 2; i < data.size(); i++)
            if (!isValidMatrixRow(data[i], 0))
                return false;
        return true;
    }

    static bool isValidMatrixRow(string row, int elements) {
        unsigned long commas = 0;
        for (int i = 0; i < row.size(); i++) {
            if (row[i] == ',')
                commas++;
            if ((row[i] < '0' || row[i] > '9') && row[i] != '.' && row[i] != ',')
                return false;
        }
        return (commas == elements)?true : false;
    }

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
                state = new State<T>(weight, i - 2, j);
                this->setState(i - 2, j, state);
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
    MazeGame(matrix states, State<T> *initialState, State<T> *goalState, unsigned long matrixSize) {
        this->statesMatrix = states;
        this->initialState = initialState;
        this->goalState = goalState;
        this->matrixSize = matrixSize;
    }

    MazeGame(matrix states, struct position initial, struct position goal, unsigned long matrixSize) {
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

    MazeGame(MazeGame<T>& mazeGame) {
        this->matrixSize = mazeGame.matrixSize;
        this->initMatrix();
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                this->statesMatrix[i][j] = new State<T>(mazeGame.getState(i,j)->getState(), i,j);
            }
        }
        this->initialState = this->getState(mazeGame.initialState->getRow(), mazeGame.initialState->getColumn());
        this->goalState = this->getState(mazeGame.goalState->getRow(), mazeGame.goalState->getColumn());

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

    virtual State<T>* getState(int row, int column) {
        return this->statesMatrix[row][column];
    }

    virtual list<State<T> *> getAllPossibleState(State<T> *state) {
        list < State<T> * > neighbors;
        if (this->isStateExist(state->getRow() - 1, state->getColumn())
            && !isWall(state->getRow() - 1, state->getColumn()))
            neighbors.push_back(this->getState(state->getRow() - 1, state->getColumn()));

        if (this->isStateExist(state->getRow(), state->getColumn() - 1)
            && !isWall(state->getRow(), state->getColumn() - 1))
            neighbors.push_back(this->getState(state->getRow(), state->getColumn() - 1));

        if (this->isStateExist(state->getRow() + 1, state->getColumn())
            && !isWall(state->getRow() + 1, state->getColumn()))
            neighbors.push_back(this->getState(state->getRow() + 1, state->getColumn()));

        if (this->isStateExist(state->getRow(), state->getColumn() + 1)
            && !isWall(state->getRow(), state->getColumn() + 1))
            neighbors.push_back(this->getState(state->getRow(), state->getColumn() + 1));

        return neighbors;
    }

    list<State<T>*> getAllStates() const {
        list<State<T>*> all;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                all.push_back(statesMatrix[i][j]);
            }
        }
        return all;
    }

    bool isWall(int row, int col) {
        return this->getState(row, col)->getState() == -1;
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
        this->statesMatrix[row][column] = state;
    }
    bool operator==(const MazeGame<T> &rhs) const {
        if (this->matrixSize != rhs.matrixSize)
            return false;
        if (*this->getInitialState() != *rhs.getInitialState())
            return false;
        if (*this->getGoalState() != *rhs.getGoalState())
            return false;
        for (int i = 0; i < rhs.matrixSize; i++) {
            for (int j = 0; j < rhs.matrixSize; j++) {
                if (((State<T>*)statesMatrix[i][j])->getState() != ((State<T>*)rhs.statesMatrix[i][j])->getState())
                    return false;
            }
        }
        return true;
    }

    bool operator<(const MazeGame<T> &rhs) const {
        if (this->matrixSize < rhs.matrixSize)
            return true;
        for (int i = 0; i < rhs.matrixSize; i++) {
            for (int j = 0; j < rhs.matrixSize; j++) {
                if (((State<T>*)this->statesMatrix[i][j])->getState() < ((State<T>*)rhs.statesMatrix[i][j])->getState())
                    return true;
            }
        }
        if (this->getInitialState()->getState() < rhs.getInitialState()->getState())
            return true;
        if (this->getGoalState()->getState() < rhs.getGoalState()->getState())
            return true;
        return false;
    }

    bool operator>(const MazeGame<T> &rhs) const {
        return (rhs < *this);
    }

    bool operator<=(const MazeGame &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const MazeGame &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const MazeGame<T> * rhs) const {
        return this == *rhs;
    }


    bool operator!=(const MazeGame<T> &rhs) const {
        return !(*this == rhs);
    }

    friend bool operator==(matrix m1, matrix m2) {
        for (int i = 0; i < m1.size(); i++) {
            for (int j = 0; j < m1.size(); j++) {
                if (((State<T>*)m1[i][j])->getState() != ((State<T>*)m1[i][j])->getState())
                    return false;
            }
        }
        return true;
    }

    template <class U>
    friend ostream& operator<<(ostream &os, const MazeGame<U> &game) {
        os << game.matrixSize << endl;
        os << game.getInitialState()->getRow() << "," << game.getInitialState()->getColumn() << endl;
        os << game.getGoalState()->getRow() << "," << game.getGoalState()->getColumn() << endl;
        for (int i = 0; i < game.matrixSize; i++) {
            vector<State<T>*> row = game.statesMatrix[i];
            for (int j = 0; j < game.matrixSize - 1; j++) {
                os << ((State<T>*)row.at(j))->getState() << ",";
            }
            os <<  ((State<T>*)row.at(game.matrixSize-1))->getState() << endl;
        }
        return os;
    }
    template <class U>
    friend istream& operator >>(istream &is, MazeGame<U> **game) {
        int matrixSize;                     // matrix size
        string buffer = "";                      // buffer of file's data
        vector<string> data;                // the game data
        if (is.eof())
            return is;
        while (buffer == "") {
            is >> buffer;
            if (is.eof())
                return is;
        }
        matrixSize = stoi(buffer);
        getline(is, buffer);
        for (int i = 0; i < matrixSize+2; i++) {
            getline(is, buffer);
            if (buffer != "")
                data.push_back(buffer);
        }
        *game = new MazeGame<U>(data);
        return is;
    }

};


#endif