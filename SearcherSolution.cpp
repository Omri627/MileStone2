#include "SearcherSolution.h"

SearcherSolution::SearcherSolution(int totalCost, int length) {
    this->totalCost = totalCost;
    this->length = length;
}

SearcherSolution::SearcherSolution(int totalCost, int length, int developStates) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = developStates;
}

SearcherSolution::SearcherSolution(int totalCost, int length, int developStates, string direction) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = developStates;
    this->direction = direction;
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
istream &operator>>(istream &is, SearcherSolution **solution) {
    string buffer;                  // solution representation
    int cost, length;               // cost, length fields of solution

    /* read solution from stream and process his data */
    is >> buffer;
    cost = stoi(buffer);
    is >> buffer;
    length = stoi(buffer);

    /* set data of solution object */
    *solution = new SearcherSolution(cost, length);
}

void SearcherSolution::readSolution(istream &is) {
    is >> this;
}

int SearcherSolution::getDevelopStates() const {
    return developStates;
}

void SearcherSolution::setDevelopStates(int developStates) {
    SearcherSolution::developStates = developStates;
}

const string &SearcherSolution::getDirection() const {
    return direction;
}

void SearcherSolution::setDirection(const string &direction) {
    SearcherSolution::direction = direction;
}


