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
string SearcherSolution::StringRepresentation() const {
    return to_string(this->totalCost) + " " + to_string(this->length);
}

void SearcherSolution::setTotalCost(int totalCost) {
    this->totalCost = totalCost;
}

void SearcherSolution::setLength(int length) {
    this->length = length;
}

/*ostream &operator<<(ostream &os, SearcherSolution const*solution) {
    os << solution->StringRepresentation() << endl;
    return os;
}*/
istream &operator>>(istream &is, SearcherSolution *solution) {
    string buffer;                  // solution representation
    int cost, length;               // cost, length fields of solution

    /* read solution from stream and process his data */
    is >> buffer;
    cost = stoi(buffer);
    is >> buffer;
    length = stoi(buffer);

    /* set data of solution object */
    solution = new SearcherSolution(cost, length);
}

void SearcherSolution::readSolution(istream &is) {
    is >> this;
}


