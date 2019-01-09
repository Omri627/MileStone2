#include "BestFirstSearch.h"

template <class Solution, class T>
Solution BestFirstSearch<Solution, T>::search(Searchable<State<T>> searchable) {
    priorityQueue.emplace(searchable.getInitialState());
    list<State<T>> closed;
    while (!priorityQueue.empty()) {
        State<T> n = priorityQueue.pop();
        if (n == searchable.getGoalState()) {
            // n is the goal return the path
            return n;// return u, or return some kind of list of back tracing
    }
        list<State<T>> neighbors = searchable.getAllPossibleState(n); //all n neighbors
        for (State<T>* s : neighbors) {
            if (!isExsist(closed,s) && isExsist(priorityQueue,s)) {
                //todo:: implement the methods, "if s is not in closed and s is not in open"
                s->setCameFrom(n);
                priorityQueue.emplace(s);
            } else {
                if (!isExsist(priorityQueue,s)) {
                    //"if s is not in open add to open"
                    priorityQueue.emplace(s);
                }
            }
        }
    }
    /*priorityQueue.emplace(searchable.getInitialState()); //insert start to the priority queue
    while (!priorityQueue.empty()) {
        State<T> u = priorityQueue.pop();
        if (u == searchable.getGoalState()) {
            // u is the goal return the path
            return u; // return u, or return some kind of list of back tracing
        } else {
            list<State<T>*> neighbors = searchable.getNeighbors(u);
            for (State<T>* v : neighbors) {
                //for each neighbor v of u
                if (v->getColor() == WHITE) {
                    //v is unvisited
                    v->setColor(GRAY);
                    v->setCameFrom(u);// i think is need to be here
                    priorityQueue.emplace(v);
                }
            }
        }
    }*/
}