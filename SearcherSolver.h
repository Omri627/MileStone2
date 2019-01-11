//
// Created by ranraboh on 09/01/19.
//

#ifndef PROJECT2_SEARCHERSOLVER_H
#define PROJECT2_SEARCHERSOLVER_H

#include "Searcher.h"
#include "Solver.h"
#include "SearcherSolution.h"
template <class T>
class SearcherSolver : public Solver<Searchable<T>* , SearcherSolution*> {
private:
    Searcher<T>* searcher;
public:
    SearcherSolver(Searcher<T>* searcher) {
        this->searcher = searcher;
    }

    virtual SearcherSolution* solve(Searchable<T>* problem) {
        return this->searcher->search(problem);
    }

    const Searcher<T>* getSearcher() const {
        return this->searcher;
    }

    void setSearcher(Searcher<T> *searcher) {
        this->searcher = searcher;
    }
};

#endif