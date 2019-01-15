#ifndef PROJECT2_MAZEGAME_H
#define PROJECT2_MAZEGAME_H

#include <map>
#include "State.h"
#include "Searchable.h"
#include "Utils.h"
#include <vector>
#include <sstream>
#include <ostream>
#include <istream>
template <class T>
class MazeGame : public Searchable<T> {
private:
    /* matrix table */
    typedef vector<vector<State<T> *>> matrix;
    unsigned long matrixSize;
    matrix statesMatrix;
    State<T> *initialState;
    State<T> *goalState;

public:
    /**
     * constructor
     * @param states all states of the maze
     * @param initialState the starting state of the maze
     * @param goalState the end state of the maze
     * @param matrixSize the size of the maze
     */
    MazeGame(matrix states, State<T> *initialState, State<T> *goalState, unsigned long matrixSize) {
        this->statesMatrix = states;
        this->initialState = initialState;
        this->goalState = goalState;
        this->matrixSize = matrixSize;
    }
    /**
     * constructor
     * @param states all states of the maze
     * @param initial the startin gstate of the maze
     * @param goal the end state of the maze
     * @param matrixSize the size of the maze
     */
    MazeGame(matrix states, struct position initial, struct position goal, unsigned long matrixSize) {
        this->states = states;
        this->initialState = getState(initial);
        this->goalState = getState(goal);
        this->matrixSize = matrixSize;
    }
    /**
     * constructor
     * @param data vector of string that each string reprasant the matrix
     */
    MazeGame(vector<string> data) {
        int elementsInRow = Utils::commansAmount(data[0]) + 1;
        int dataSize = data.size() - 2;
        this->matrixSize = max(elementsInRow, dataSize);
        this->initMatrix(dataSize, elementsInRow);
        this->createMazeFromData(data);
    }
    /**
     * constructor
     * @param mazeGame other maze game
     */
    MazeGame(MazeGame<T>& mazeGame) {
        this->matrixSize = mazeGame.matrixSize;
        this->initMatrix(mazeGame.matrixSize, mazeGame.matrixSize);
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                //copy the maze game
                this->statesMatrix[i][j] = new State<T>(mazeGame.getState(i,j)->getState(), i,j);
            }
        }
        //set the goal and initial states
        this->initialState = this->getState(mazeGame.initialState->getRow(), mazeGame.initialState->getColumn());
        this->goalState = this->getState(mazeGame.goalState->getRow(), mazeGame.goalState->getColumn());

    }
    /**
     * get state
     * @param position
     * @return
     */
    virtual State<T> *getState(position position) {
        return this->statesMatrix[position.row][position.column];
    }
    /**
     * check if state exist
     * @param position given position
     * @return true if state exist else false
     */
    virtual bool isStateExist(position position) {
        if (position.row > this->matrixSize - 1 || position.row < 0
            || position.column > this->matrixSize - 1 || position.column < 0)
            return false;
        return true;
    }
    /**
     * check if state exist
     * @param row index
     * @param column index
     * @return true if  state exist else false
     */
    virtual bool isStateExist(int row, int column) {
        if (row > this->matrixSize - 1 || row < 0
            || column > this->matrixSize - 1 || column < 0)
            return false;
        return true;
    }
    /**
     * get state from index of position
     * @param row index
     * @param column index
     * @return the state in the position
     */
    virtual State<T>* getState(int row, int column) {
        return this->statesMatrix[row][column];
    }
    /**
     * get all possible negihbor of state
     * @param state current state
     * @return all negihbor of current state
     */
    virtual list<State<T> *> getAllPossibleState(State<T> *state) {
        list < State<T> * > neighbors;
        //return all surrounded state
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
    /**
     *
     * @return list of all state in the matrix
     */
    list<State<T>*> getAllStates() const {
        list<State<T>*> all;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                all.push_back(statesMatrix[i][j]);
            }
        }
        return all;
    }
    /**
     * check if in given position ther is a wall (-1)
     * @param row index
     * @param col index
     * @return true if is wall, else false
     */
    bool isWall(int row, int col) {
        return this->getState(row, col)->getState() == -1;
    }
    /**
     * getter for initial state
     * @return initial state
     */
    State<T> *getInitialState() const {
        return this->initialState;
    }
    /**
     * set initial state
     * @param initialState state
     */
    void setInitialState(State<T> *initialState) {
        this->initialState = initialState;
    }
    /**
     * get goal state
     * @return goal state
     */
    State<T> *getGoalState() const {
        return this->goalState;
    }
    /**
     * setter for goal state
     * @param goalState state
     */
    void setGoalState(State<T> *goalState) {
        this->goalState = goalState;
    }
    /**
     * set goal state by index
     * @param row index
     * @param column index
     * @param state goal state
     */
    void setState(int row, int column, State<T> *state) {
        if (!this->statesMatrix[row][column])
            delete(this->statesMatrix[row][column]);
        this->statesMatrix[row][column] = state;
    }
    /* operator >, >=, <, <= , ==, != used to compare between maze game objects.
* aid map to order the problems and identify that two mazeGame problems are equal*/
    /**
     * operator <
     * @param rhs other mazeGame
     * @return true if less
     */
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
   /**
    * cehcek that both mazeGame are equals
    * @param rhs other MazeGame
    * @return true if equal else false
    */
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
    /**
     * grater then
     * @param rhs other mazeGame
     * @return true if grater
     */
    bool operator>(const MazeGame<T> &rhs) const {
        return (rhs < *this);
    }
    /**
     * lessEqual operator
     * @param rhs other mazeGame
     * @return true if lessEqual
     */
    bool operator<=(const MazeGame &rhs) const {
        return !(rhs < *this);
    }
    /**
     * graterEqual operator
     * @param rhs other mazeGame
     * @return true if graterEqual
     */
    bool operator>=(const MazeGame &rhs) const {
        return !(*this < rhs);
    }
    /**
     * equal operator
     * @param rhs pointer MazeGame
     * @return true if equal
     */
    bool operator==(const MazeGame<T> * rhs) const {
        return this == *rhs;
    }

    /**
     * not equal operator
     * @param rhs other MazeGame
     * @return true if not equal
     */
    bool operator!=(const MazeGame<T> &rhs) const {
        return !(*this == rhs);
    }
    /**
     * equal between two matrixes
     * @param m1 matrix
     * @param m2 matrix
     * @return true if equal
     */
    friend bool operator==(matrix m1, matrix m2) {
        for (int i = 0; i < m1.size(); i++) {
            for (int j = 0; j < m1.size(); j++) {
                if (((State<T>*)m1[i][j])->getState() != ((State<T>*)m1[i][j])->getState())
                    return false;
            }
        }
        return true;
    }
    /**
     * ostream operator for MazeGame
     * @param os ostream
     * @param game MazeGaem
     * @return ostram
     */
    template <class U>
    friend ostream& operator<<(ostream &os, const MazeGame<U> &game) {
        os << game.matrixSize << endl;
        //stream out the rows of the matrix
        for (int i = 0; i < game.matrixSize; i++) {
            vector<State<T>*> row = game.statesMatrix[i];
            for (int j = 0; j < game.matrixSize - 1; j++) {
                os << ((State<T>*)row.at(j))->getState() << ",";
            }
            os <<  ((State<T>*)row.at(game.matrixSize-1))->getState() << endl;
        }
        //stream out the initial goal and end goal
        os << game.getInitialState()->getRow() << "," << game.getInitialState()->getColumn() << endl;
        os << game.getGoalState()->getRow() << "," << game.getGoalState()->getColumn() << endl;
        return os;
    }
    /**
     * instream operator for MazeGame
     * @param is istream
     * @param game MazeGame
     * @return istream
     */
    template <class U>
    friend istream& operator >>(istream &is, MazeGame<U> **game) {
        int matrixSize;                     // matrix size
        string buffer = "";                 // buffer of file's data
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
        //stream in matrix rows
        for (int i = 0; i < matrixSize+2; i++) {
            getline(is, buffer);
            if (buffer != "")
                data.push_back(buffer);
        }
        *game = new MazeGame<U>(data);
        return is;
    }

private:
    /**
     * initialize the matrix with null
     * @param row rows of the matrix
     * @param column columns of the matrix
     */
    void initMatrix(int row, int column) {
        for (int i = 0; i < row; i++) {
            vector<State<T> *> rowVector;
            for (int j = 0; j < column; j++) {
                rowVector.push_back(nullptr);
            }
            this->statesMatrix.push_back(rowVector);
        }
    }
    /**
     * if the matrix is rectangle, fill it with walls to make it squre
     */
    void fillWalls() {
        int walls = this->matrixSize - this->statesMatrix[0].size();
        int emptyLines = this->matrixSize - this->statesMatrix.size();
        //check if need to add walls in the bottom
        if (walls > 0) {
            for (int i = 0; i < this->matrixSize; ++i) {
                vector<State<T> *> *rowVector = &this->statesMatrix[i];
                for (int j = 0; j < walls; ++j) {
                    rowVector->push_back(new State<T>(-1, i, rowVector->size()));
                }
            }
        } //check if need to add walls on the side
        else if (emptyLines > 0) {
            for (int i = 0; i < emptyLines; i++) {
                vector<State<T> *> rowVector;
                for (int j = 0; j < this->matrixSize; j++) {
                    rowVector.push_back(new State<T>(-1, statesMatrix.size(), j));
                }
                this->statesMatrix.push_back(rowVector);
            }
        }

    }
    /**
     * cehck if the vector of string contains valid data
     * @param data the vector of strings
     * @return true if valid
     */
    bool isValidData(vector<string> data) {
        int elementsInRow = Utils::commansAmount(data[0]);
        //check that initial goal and start goal is valid
        if (!isValidMatrixRow(data[data.size()-1], 1) || !isValidMatrixRow(data[data.size()-2], 1))
            return false;
        //check that matrix rows is valid
        for (int i = 0; i < data.size() - 2; i++)
            if (!isValidMatrixRow(data[i], elementsInRow))
                return false;
        return true;
    }
    /**
     * check if row is valid, so it contains enough commas to elements
     * @param row row to be checked
     * @param elements
     * @return true if valid row
     */
    static bool isValidMatrixRow(string row, int elements) {
        stringstream ss(row);
        int num;
        int commas = 0;
        while (ss >> num) {
            if (ss.peek() == ',') {
                ss.ignore();
                commas++;
            }
        }
        return (commas == elements);
    }
    /**
     * create maze from data of row
     * @param data vector of string that reprsant rows in the matrix
     * @return MazeGame
     */
    MazeGame<T> *createMazeFromData(vector<string> data) {
        position initialPosition;
        position goalPosition;
        const char *buffer;
        T weight;
        State<T> *state;
        char delimiter;
        if (!this->isValidData(data)) //check if data is valid
            throw "invalid data";
        for (int i = 0, j = 0; i < data.size() - 2; i++) {
            string row = data.at(i);
            istringstream rowStream(row);
            j = 0;
            //create state from elements in the row of the data
            while (rowStream >> weight) {
                state = new State<T>(weight, i, j);
                this->setState(i, j, state);
                rowStream >> delimiter;
                j++;
            }
        }
        //fill with wall if it is rectangle
        this->fillWalls();
        //create the goal and initial states
        buffer = data[data.size()-2].c_str();
        sscanf(buffer, "%d,%d", &initialPosition.row, &initialPosition.column);
        buffer = data[data.size()-1].c_str();
        sscanf(buffer, "%d,%d", &goalPosition.row, &goalPosition.column);
        this->initialState = getState(initialPosition);
        this->goalState = getState(goalPosition);
    }

public:
    /**
     * destructor
     */
    virtual ~MazeGame() {
        //free all states
        for (int i = 0; i < matrixSize ; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                if(statesMatrix[i][j] != nullptr) {
                    delete statesMatrix[i][j];
                    statesMatrix[i][j] = nullptr;
                }
            }

        }
        this->statesMatrix.clear();
    }
};


#endif