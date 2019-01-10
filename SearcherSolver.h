//
// Created by ranraboh on 09/01/19.
//

#ifndef PROJECT2_SEARCHERSOLVER_H
#define PROJECT2_SEARCHERSOLVER_H

#include "Searcher.h"
#include "Solver.h"
#include "SearcherSolution.h"
template <class T>
class SearcherSolver : public Solver<Searchable<T>* , Solution*> {
private:
    Searcher<T>* searcher;
public:
    SearcherSolver(Searcher<T>* searcher);

    virtual Solution* solve(Searchable<T>* problem);

    const Searcher<T>* getSearcher() const;

    void setSearcher(Searcher<T> *searcher);
};
#endif