//
// Created by ranraboh on 09/01/19.
//

#include "SearcherSolver.h"
template<class T>
void SearcherSolver<T>::setSearcher(Searcher<T>*searcher) {
    this->searcher = searcher;
}

template<class T>
const Searcher<T>* SearcherSolver<T>::getSearcher() const {
    return this->searcher;
}

template<class T>
Solution* SearcherSolver<T>::solve(Searchable<T>* problem) {
    return this->searcher->search(problem);
}
template<class T>
SearcherSolver<T>::SearcherSolver(Searcher<T> *searcher) {
    this->searcher = searcher;
}
