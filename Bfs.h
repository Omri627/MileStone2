#ifndef BREADTH_FIRST_SEARCH
    #define BREADTH_FIRST_SEARCH

    #include "Searcher.h"
#include "MazeGame.h"
#include "SearcherSolution.h"
#include "StatePriorityQueue.h"
template <class T>
class Bfs : public Searcher<T> {
private:
    void initialize(Searchable<T>* searchable) {
        searchable->getInitialState()->setCost(0);
        searchable->getInitialState()->setColor(GRAY);
    }

    void bfsAlgorithm(Searchable<T> *searchable) {
        StatePriorityQueue<State<T>*> priorityQueue;
        priorityQueue.push(searchable->getInitialState());
        State<T>* state;
        list<State<T>*> neighbors;
        while (!priorityQueue.empty()) {
            state = priorityQueue.top();
            neighbors = searchable->getAllPossibleState(state);
            for (State<T>* neighbor : neighbors) {
                this->relax(state, neighbor);
                if (neighbor->getColor() == WHITE) {
                    neighbor->setColor(GRAY);
                    priorityQueue.push(neighbor);
                }
            }
            state->setColor(BLACK);
            priorityQueue.pop();
        }
    }
public:
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        int cost, length;
        this->initialize(searchable);
        this->bfsAlgorithm(searchable);
        cost = searchable->getGoalState()->getCost();
        length = this->getLengthOfPath(searchable->getInitialState(), searchable->getGoalState());
        return new SearcherSolution(cost, length);
    }

};
#endif