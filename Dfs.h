#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include "SearcherSolution.h"
#include "Searcher.h"
template <class T>
class Dfs : public Searcher<T> {
private:
    /**
    * initialize: prep instructions required for the algorithm
    * @param searchable searchable object
    */
    void initialize(Searchable<T>* searchable) {
        searchable->getInitialState()->setCost(0);
        searchable->getInitialState()->setColor(GRAY);
    }
    /**
    * dfs algorithm gets a searchable object
    * and find a path from initial state to goal state (if there any)
    * the algorithm traverse the graph as follows:
    * explores as far as possible along each branch before backtracking.
    * @param searchable searchable object
    */
    void dfsVisit(State<T>* state, Searchable<T>* searchable) {
        state->setColor(GRAY);
        //cout << "(" << state->getRow() << "," << state->getColumn() << ")" << endl;
        list < State<T> *> neighbors = searchable->getAllPossibleState(state);
        for (State<T>* neighbor : neighbors) {
            this->relax(state, neighbor);
            if (neighbor->getColor() == WHITE) {
                neighbor->setCameFrom(state);
                dfsVisit(neighbor, searchable);
            }
        }
        state->setColor(BLACK);
    }
public:
    /* empty constructor */
    Dfs() {}
    /**
    * search method gets a searchable object and using the bfs algorithm
    * it found the shortest path.
    * and returns the a solution compose of
    * cost, length of the shortest path, number of develop states.
    * and the direction from intial state to goal state.
    * @param searchable searchable object
    * @return returns solution of specific searchable problem.
    */
    virtual SearcherSolution* search(Searchable<T>* searchable) {
        int cost, sum;                  // cost and sum of path
        initialize(searchable);
        dfsVisit(searchable->getInitialState(), searchable);
        cost = this->getCostOfPath(searchable->getInitialState(), searchable->getGoalState());
        sum = this->getLengthOfPath(searchable->getInitialState(), searchable->getGoalState());
        if (cost == -1) {
            return new SearcherSolution(-1, -1);
        }
        int develops = this->getDevelopStates(searchable->getAllStates());
        string direction = this->getDirection(searchable->getInitialState(), searchable->getGoalState());
        return new SearcherSolution(cost, sum, develops, direction);
    }
};


#endif