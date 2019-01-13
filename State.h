
#ifndef PROJECT2_STATE_H
    #define PROJECT2_STATE_H

#include <string>
using namespace std;
/**
 * To keep track of its progress, searcher algorithms colors each of the states.
 * All the vertices are initialized to white when they are constructed.
 * A white vertex is an undiscovered state
 * When a state is initially discovered it is colored gray,
 * and when searcher algorithm has completely explored a state it is colored black
 */
enum color {
    WHITE, GRAY, BLACK
};
template <class T> class State {
private:
    /* value of state */
    T state;
    /* number of row in matrix */
    int row;
    /* number of column in matrix */
    int column;
    /* cost of shortest path */
    double cost;
    /* the state that came from this state in seacher algorithm.
     * assist in determining the shortest path tree */
    State<T> *cameFrom;
    /* color of state aid searcher algorithms to mark state */
    enum color color;
public:
    /**
     * create new State object initialized with given value.
     * @param state value
     */
    State(T state) : state(state) {
        this->cameFrom = nullptr;
        this->color = WHITE;
        this->cost = -1;
    }
    /**
     * create new State object initialized with given value and cost.
     * @param state value
     * @param cost cost
     */
    State(T state, double cost) : state(state), cost(cost) {
        this->cameFrom = nullptr;
        this->color = WHITE;
        this->cost = -1;
    }
    /**
     * create new State object initialized with given value, row and column.
     * @param state value
     * @param row number of row
     * @param column number of column
     */
    State(T state, int row, int column) : state(state), row(row), column(column) {
        this->cameFrom = nullptr;
        this->color = WHITE;
        this->cost = -1;
    }
    /**
     * empty constructor
     */
    State() {}
    /**
     * getter method of value field
     * @return returns the value of this state.
     */
    T getState() const {
        return this->state;
    }
    /**
     * getter method of row field
     * @return returns number of row of this state.
     */
    int getRow() const {
        return this->row;
    }
    /**
     * getter method of row field
     * @return returns the color of this state.
     */
    const enum color getColor() const {
        return this->color;
    }
    /**
     * getter method of column field
     * @return returns number of column of this state.
     */
    int getColumn() const {
        return this->column;
    }
    /**
     * getter method of cost field
     * @return returns the cost of this state.
     */
    double getCost() const {
        return this->cost;
    }
    /**
     * getter method of cameFrom field
     * @return returns the state that came before this state in searcher algorithm.
     */
    State<T> *getCameFrom() {
        return this->cameFrom;
    }
    /**
     * setCameFrom method sets the state which came before this state in searcher algorithm.
     * @param cameFrom state object.
     */
    void setCameFrom(State<T> *cameFrom) {
        this->cameFrom = cameFrom;
    }
    /**
     * setCost sets the cost of shortest path in searcher algorithms.
     * @param cost cost value
     */
    void setCost(double cost) {
        this->cost = cost;
    }
    /**
     * setColor method sets the color of this state.
     * @param color specific color
     */
    void setColor(enum color color) {
        this->color = color;
    }
    /* operator >, >=, <, <= , ==, != used to compare between state objects.
     * aid priority queue to order the states by their cost value
     * and dequeue the lower costs states first */
    bool operator<(const State &rhs) const {
        return cost < rhs.cost;
    }
    bool operator>(const State &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const State &rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const State &rhs) const {
        return !(*this < rhs);
    }
    bool operator==(const State &rhs) const {
        return this->cost == rhs.cost;
    }
    bool operator!=(const State &rhs) const {
        return this->cost != rhs.cost;
    }
};

#endif //PROJECT2_STATE_H
