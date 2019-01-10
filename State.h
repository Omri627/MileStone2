
#ifndef PROJECT2_STATE_H
    #define PROJECT2_STATE_H

#include <string>
using namespace std;
enum color {
    WHITE, GRAY, BLACK
};
template <class T> class State {
private:
    T state;
    int row;
    int column;
    double cost;
    State<T>* cameFrom;
    enum color color;
public:
    State(T state) : state(state) {
        this->cameFrom = nullptr;
        this->color = WHITE;
    }

    State(T state, double cost) : state(state), cost(cost) {
        this->cameFrom = nullptr;
        this->color = WHITE;
    }

    State(T state, int row, int column) : state(state), row(row), column(column) {
        this->cameFrom = nullptr;
        this->color = WHITE;
    }

    State() {}

    T getState() const {
        return this->state;
    }

    int getRow() const {
        return this->row;
    }

    const enum color getColor() const {
        return color;
    }

    int getColumn() const {
        return this->column;
    }

    double getCost() const {
        return this->cost;
    }


    const State<T> *getCameFrom() {
        return this->cameFrom;
    }

    void setCameFrom(State<T> *cameFrom) {
        this->cameFrom = cameFrom;
    }

    void setCost(double cost) {
        this->cost = cost;
    }

    void setColor(enum color color) {
        this->color = color;
    }

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
        return this->state == rhs.state;
    }
};

#endif //PROJECT2_STATE_H
