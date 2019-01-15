//
// Created by ranraboh on 09/01/19.
//

#ifndef PROJECT2_SEARCHERSOLVER_H
#define PROJECT2_SEARCHERSOLVER_H

#include "Searcher.h"
#include "Solver.h"
#include "SearcherSolution.h"
template <class T>
/* object adapter pattern: allows the interface of an searcher algorithms to be used as solvers.
 * without modifying their source code. */
class SearcherSolver : public Solver<Searchable<T>* , SearcherSolution*> {
private:
    /* searcher object which has the ability to solve searchable problems */
    Searcher<T>* searcher;
public:
    /**
     * creates SearcherSolver object with given searcher algorithm.
     * @param searcher searcher algorithm
     */
    SearcherSolver(Searcher<T>* searcher) {
        this->searcher = searcher;
    }
    /**
     * solve method gets a searchable problem (as board game, graphs, matrix)
     * and solve it. means find the shortest path from two particular nodes/elements.
     * @param problem searchable object.
     * @return returns solution for specific searchable problem.
     */
    virtual SearcherSolution* solve(Searchable<T>* problem) {
        return this->searcher->search(problem);
    }
    /**
     * getter method of searcher field.
     * @return returns searcher object.
     */
    const Searcher<T>* getSearcher() const {
        return this->searcher;
    }
    /**
     * setter method of searcher field.
     * used to set searcher object.
     * @param searcher searcher object.
     */
    void setSearcher(Searcher<T> *searcher) {
        this->searcher = searcher;
    }
};

#endif