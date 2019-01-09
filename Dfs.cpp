
#include "Dfs.h"
#include "SearcherSolution.h"
template <class T>
void Dfs<T>::initializeSinglePair(Searchable<State<T>> searchable) {
    typename map<position,  State<T>>::iterator iterator;
    iterator = searchable.getStates().begin();
    while (iterator != searchable.getStates().end()) {
        iterator->second.setCost(1000);
        iterator++;
    }
    searchable.getInitialState().setCost(0);
}

template<class T>
Solution* Dfs<T>::search(Searchable<State<T>> searchable) {
    int cost, sum;
    dfsVisit(searchable.getInitialState(), searchable);
    cost = this->getCostOfPath(searchable.getInitialState(), searchable.getGoalState());
    sum = this->getLengthOfPath(searchable.getInitialState(), searchable.getGoalState());
    return new SearcherSolution(cost, sum);
}

template<class T>
void Dfs<T>::dfsVisit(State<T> state, Searchable<State<T>> searchable) {
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
