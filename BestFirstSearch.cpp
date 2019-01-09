#include "BestFirstSearch.h"
#include "SearcherSolution.h"

template <class T>
Solution* BestFirstSearch<T>::search(Searchable<State<T>> searchable) {
    double newPath = 0;
    double oldPath = -1;
    priorityQueue.emplace(searchable.getInitialState());
    searchable.getInitialState().setColor(GRAY); //is state inside the pq is color is gray

    while (!priorityQueue.empty()) {
        State<T> n = priorityQueue.pop();
        n.setColor(BLACK); //color is black so we won't check n again
        if (n == searchable.getGoalState()) {
            double sum = getCostOfPath(searchable.getInitialState(), n);
            double length = getLengthOfPath(searchable.getInitialState(), n);
            if (sum != -1 && length != -1) {
                return new SearcherSolution(sum, length);
            }
            return new SearcherSolution(-1, -1);
        }

        list<State<T>> neighbors = searchable.getAllPossibleState(n); //all n neighbors
        for (State<T> s : neighbors) {
            if ((s.getColor() != BLACK) && (s.getColor() != GRAY)) {
                s->setCameFrom(n);
                s.setColor(GRAY); //color is gray because we add it to queue
                priorityQueue.emplace(s);
            } else {
                newPath = getCostOfPath(searchable.getInitialState(), s);
                if (newPath < oldPath || oldPath == -1) { //old path will be -1 only at the beginning
                    if (s.getColor() != GRAY) {
                        //if s is not in pq add to pq
                        priorityQueue.emplace(s);
                        oldPath = newPath;
                    } else {
                        priorityQueue.remove(s);
                        priorityQueue.emplace(s);
                    }
                }
            }
        }
    }
}