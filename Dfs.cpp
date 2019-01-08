
#include "Dfs.h"
template <class Solution, class T>
void Dfs<Solution, T>::initializeSinglePair(Searchable<State<T>> searchable) {
    typename map<position,  State<T>>::iterator iterator;
    iterator = searchable.getStates().begin();
    while (iterator != searchable.getStates().end()) {
        iterator->second.setCost(1000);
        iterator++;
    }
    searchable.getInitialState().setCost(0);
}

template<class Solution, class T>
Solution Dfs<Solution, T>::search(Searchable<State<T>> searchable) {
    dfsVisit(searchable.getInitialState(), searchable);

}

template<class Solution, class T>
void Dfs<Solution, T>::dfsVisit(State<T> state, Searchable<State<T>> searchable) {
    static int t = 0;
    state.setColor(GRAY);
    list < State<T>> neighbors = searchable.getStates();
    for (State<T> neighbor : neighbors) {
        if (neighbor == searchable.getGoalState()) {
            neighbor.setCameFrom(state);
            break;
        }
        if (neighbor.getColor() == WHITE) {
            dfsVisit(neighbor, searchable.getAllPossibleState(neighbor));
            neighbor.setCameFrom(state);
        }
    }
    state.setColor(BLACK);
    state.setCost(t);
    t = t + 1;
}
