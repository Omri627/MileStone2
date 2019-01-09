//
// Created by ranraboh on 09/01/19.
//

#include "SearcherSolution.h"

SearcherSolution::SearcherSolution(int totalCost, int length) {
    this->totalCost = totalCost;
    this->length = length;
}

int SearcherSolution::getTotalCost() const {
    return this->totalCost;
}

int SearcherSolution::getLength() const {
    return this->length;
}
string SearcherSolution::StringRepresentation() {
    return this->totalCost + "$" + this->length;
}

void SearcherSolution::setTotalCost(int totalCost) {
    SearcherSolution::totalCost = totalCost;
}

void SearcherSolution::setLength(int length) {
    SearcherSolution::length = length;
}
