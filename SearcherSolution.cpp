#include "SearcherSolution.h"

SearcherSolution::SearcherSolution(int totalCost, int length) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = 0;
    this->direction ="";
}

SearcherSolution::SearcherSolution(int totalCost, int length, int developStates) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = developStates;
    this->direction ="";
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
string SearcherSolution::fileRepresentation() const {
    return to_string(this->totalCost) + " " + to_string(this->length) + " " + to_string(this->developStates) + "\n" +
    this->direction;
}
string SearcherSolution::StringRepresentation() const {
    return this->direction;
}
void SearcherSolution::setTotalCost(int totalCost) {
    this->totalCost = totalCost;
}

void SearcherSolution::setLength(int length) {
    this->length = length;
}

ostream &operator<<(ostream &os, SearcherSolution *solution) {
    os << solution->fileRepresentation() << endl;
    return os;
}
istream &operator>>(istream &is, SearcherSolution **solution) {
    string buffer;                  // solution representation
    int cost, length, develope;               // cost, length fields of solution
    char delimiter;
    /* read solution from stream and process his data */
    getline(is, buffer);
    getline(is, buffer);
    sscanf(buffer.c_str(), "%d %d %d", &cost, &length, &develope);
    getline(is, buffer);

    /* set data of solution object */
    *solution = new SearcherSolution(cost, length, develope, buffer);
}

void SearcherSolution::readSolution(istream &is) {
    is >> this;
}

int SearcherSolution::getDevelopStates() const {
    return developStates;
}

void SearcherSolution::setDevelopStates(int developStates) {
    this->developStates = developStates;
}

const string &SearcherSolution::getDirection() const {
    return direction;
}

void SearcherSolution::setDirection(const string &direction) {
    this->direction = direction;
}


