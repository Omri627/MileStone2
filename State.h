
#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H


template <class T> class State {
private:
    T state;
    double cost;
    State<T> cameFrom;

public:
    State(T state) : state(state) {}

    State(T state, double cost) : state(state), cost(cost) {}

    void setCameFrom(const State<T> &cameFrom) {
        State::cameFrom = cameFrom;
    }
};


#endif //PROJECT2_STATE_H
