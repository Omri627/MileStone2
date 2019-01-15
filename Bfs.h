#ifndef BREADTH_FIRST_SEARCH
    #define BREADTH_FIRST_SEARCH

#include "Searcher.h"
#include "MazeGame.h"
#include "SearcherSolution.h"
#include "StatePriorityQueue.h"
template <class T>
class Bfs : public Searcher<T> {
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
     * bfs algorithm gets a searchable object
     * and find the optimal path from initial state to goal state.
     * the algorithm traverse the graph as follows:
     * explores all of the neighbor nodes at the present depth prior to
     * moving on to the nodes at the next depth level.
     * @param searchable searchable object
     */
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
    /**
     * search method gets a searchable object and using the bfs algorithm
     * it found the shortest path.
     * and returns the a solution compose of
     * cost, length of the shortest path, number of develop states.
     * and the direction from intial state to goal state.
     * @param searchable searchable object
     * @return returns solution of specific searchable problem.
     */
    virtual SearcherSolution *search(Searchable<T> *searchable) {
        int cost, length;
        this->initialize(searchable);
        this->bfsAlgorithm(searchable);
        cost = this->getCostOfPath(searchable->getInitialState(), searchable->getGoalState());
        length = this->getLengthOfPath(searchable->getInitialState(), searchable->getGoalState());
        if (cost == -1) {
            return new SearcherSolution(-1, -1);
        }
        int develops = this->getDevelopStates(searchable->getAllStates());
        string direction = this->getDirection(searchable->getInitialState(), searchable->getGoalState());
        return new SearcherSolution(cost, length,develops ,direction);
    }

};
#endif