#include "SearcherSolution.h"
/**
 * creates SearcherSolution object initialized with given cost and length.
 * @param totalCost total cost of shortest path from initial state to goal state
 * @param length length of shortest path from initial state to goal state
 */
SearcherSolution::SearcherSolution(int totalCost, int length) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = 0;
    this->direction ="";
}
/**
 * creates SearcherSolution object initialized with given
 * cost, number of developed states and length.
 * @param totalCost total cost of shortest path from initial state to goal state
 * @param length length of shortest path from initial state to goal state
 * @param developStates number of develop states in search
 */
SearcherSolution::SearcherSolution(int totalCost, int length, int developStates) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = developStates;
    this->direction ="";
}
/**
 * creates SearcherSolution object initialized with given
 * cost, number of developed states and length and direction
 * from initial state to goal state.
 * @param totalCost total cost of shortest path from initial state to goal state
 * @param length length of shortest path from initial state to goal state
 * @param developStates number of develop states in search
 * @param direction direction of shortest path from initial state to goal state
 */
SearcherSolution::SearcherSolution(int totalCost, int length, int developStates, string direction) {
    this->totalCost = totalCost;
    this->length = length;
    this->developStates = developStates;
    this->direction = direction;
}
/**
 * getter method of totalCost field
 * @return returns total cost of shortest path from initial state to goal state
 */
int SearcherSolution::getTotalCost() const {
    return this->totalCost;
}
/**
 * getter method of length field
 * @return returns length of shortest path from initial state to goal state
 */
int SearcherSolution::getLength() const {
    return this->length;
}
/**
 * provide a format for textual representation of solution in file
 * @return returns file representation of this solution.
 */
string SearcherSolution::fileRepresentation() const {
    return to_string(this->totalCost) + " " + to_string(this->length) + " " + to_string(this->developStates) + "\n" +
    this->direction;
}
/**
* StringRepresentation method returns the textual representation of solution
* which print out on screen and stored in file.
* @return returns the textual representation of solution
*/
string SearcherSolution::StringRepresentation() const {
    return this->direction;
}
/**
 * setter method of totalCost field.
 * used to set the cost of solution / shortest path.
 * @param totalCost total cost of shortest path from initial state to goal state
 */
void SearcherSolution::setTotalCost(int totalCost) {
    this->totalCost = totalCost;
}
/**
 * setter method of length field.
 * used to set the length of solution / shortest path.
 * @param length length of shortest path from initial state to goal state
 */
void SearcherSolution::setLength(int length) {
    this->length = length;
}
/**
 * make solution object streamable.
 * and provide a format for writing the object to a text stream.
 * @param os output stream object
 * @param solution specific solution
 * @return returns output stream for chaining.
 */
ostream &operator<<(ostream &os, SearcherSolution *solution) {
    os << solution->fileRepresentation() << endl;
    return os;
}
/**
* make searcher solution streamable
* and provide a format for read the object from a text stream
* @param is input stream object
* @param solution specific searcher solution object
* @return return input stream for chaining.
*/
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
/**
 * readSolution method gets input stream object and reads
 * the solution for it.
 * @param is input stream object
 */
void SearcherSolution::readSolution(istream &is) {
    is >> this;
}
/**
 * getter method of develop states field.
 * @return returns number of develop states in search
 */
int SearcherSolution::getDevelopStates() const {
    return developStates;
}
/**
 * setter method of develop states field.
 * sets the number of develop states in search.
 * @param developStates number of develop states in search
 */
void SearcherSolution::setDevelopStates(int developStates) {
    this->developStates = developStates;
}
/**
 * getter method of direction field
 * @return returns direction of shortest path from initial state to goal state
 */
const string &SearcherSolution::getDirection() const {
    return direction;
}
/**
 * setter method of direction field.
 * @param direction direction of shortest path from initial state to goal state
 */
void SearcherSolution::setDirection(const string &direction) {
    this->direction = direction;
}


