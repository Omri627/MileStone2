#include <vector>
#include <sstream>
#include "MazeGame.h"
#include "Searchable.h"

template<class T>
MazeGame<T>::MazeGame(map < struct position, State<T> > states, State<T> initialState, State<T> goalState) {
    this->states = states;
    this->initialState = initialState;
    this->goalState = goalState;
}
template<class T>
MazeGame<T>::MazeGame(map < position, State<T> > states, struct position initial, struct position goal) {
    this->states = states;
    this->initialState = getState(initial);
    this->goalState = getState(goal);
}
template<class T>
State<T> MazeGame<T>::getState(int row, int column) {
    struct position position;
    position.row = row;
    position.column = column;
    return this->getState(position);
}

template<class T>
bool MazeGame<T>::isStateExist(position position) {
    typename list<State<T>>::iterator iterator;
    iterator = this->states.find(position);
    if (iterator == this->states.end())
        return false;
    return true;
}
template<class T>
State<T> MazeGame<T>::getState(position position) {
    return this->states[position];
}
template<class T>
State<T> MazeGame<T>::getInitialState() {
    return this->initialState;
}

template<class T>
State<T> MazeGame<T>::getGoalState() {
    return this->goalState;
}

template<class T>
list< State<T> > MazeGame<T>::getAllPossibleState(State<T> state) {
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
template<class T>
MazeGame<T>* MazeGame<T>::createMazeFromData(vector<string> data) {
    position initialPosition;
    position goalPosition;
    position nodePoistion;
    map < position, State<T> > states;
    const char* buffer;
    T weight;
    State<T> state;
    char delimiter;
    for (int i = 0, j = 0; i < data.size() - 2; i++) {
        istringstream rowStream(data[i]);
        j = 0;
        while (rowStream >> weight) {
            nodePoistion.row = i;
            nodePoistion.column = j;
            state = new State<T>(weight, i, j);
            states[nodePoistion] = state;
            rowStream >> delimiter;
            j++;
        }
    }
    buffer = data[data.size() - 2].c_str();
    sscanf(buffer, "%d,%d", &initialPosition.row, &initialPosition.column);
    buffer = data[data.size() - 1].c_str();
    sscanf(buffer, "%d,%d", &goalPosition.row, &goalPosition.column);
    return new MazeGame(states, initialPosition, goalPosition);
}

template<class T>
map< position, State<T>> MazeGame<T>::getStates() {
    return this->states;
}
