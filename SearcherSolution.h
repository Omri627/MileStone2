#ifndef PROJECT2_SEARCHERSOLUTION_H
#define PROJECT2_SEARCHERSOLUTION_H

#include "Solution.h"
using namespace std;
class SearcherSolution : public Solution {
private:
    /* total cost of shortest path from initial state to goal state */
    int totalCost;
    /* length of shortest path from initial state to goal state */
    int length;
    /* number of develop states in search */
    int developStates;
    /* direction of shortest path from initial state to goal state */
    string direction;
public:
    /**
     * creates SearcherSolution object initialized with given cost and length.
     * @param totalCost total cost of shortest path from initial state to goal state
     * @param length length of shortest path from initial state to goal state
     */
    SearcherSolution(int totalCost, int length);
    /**
     * creates SearcherSolution object initialized with given
     * cost, number of developed states and length.
     * @param totalCost total cost of shortest path from initial state to goal state
     * @param length length of shortest path from initial state to goal state
     * @param developStates number of develop states in search
     */
    SearcherSolution(int totalCost, int length, int developStates);
    /**
     * creates SearcherSolution object initialized with given
     * cost, number of developed states and length and direction
     * from initial state to goal state.
     * @param totalCost total cost of shortest path from initial state to goal state
     * @param length length of shortest path from initial state to goal state
     * @param developStates number of develop states in search
     * @param direction direction of shortest path from initial state to goal state
     */
    SearcherSolution(int totalCost, int length, int developStates, string direction);
    /**
     * getter method of totalCost field
     * @return returns total cost of shortest path from initial state to goal state
     */
    int getTotalCost() const;
    /**
     * getter method of length field
     * @return returns length of shortest path from initial state to goal state
     */
    int getLength() const;
    /**
     * setter method of totalCost field.
     * used to set the cost of solution / shortest path.
     * @param totalCost total cost of shortest path from initial state to goal state
     */
    void setTotalCost(int totalCost);
    /**
     * setter method of length field.
     * used to set the length of solution / shortest path.
     * @param length length of shortest path from initial state to goal state
     */
    void setLength(int length);
    /**
     * getter method of develop states field.
     * @return returns number of develop states in search
     */
    int getDevelopStates() const;
    /**
     * setter method of develop states field.
     * sets the number of develop states in search.
     * @param developStates number of develop states in search
     */
    void setDevelopStates(int developStates);
    /**
     * getter method of direction field
     * @return returns direction of shortest path from initial state to goal state
     */
    const string &getDirection() const;
    /**
     * setter method of direction field.
     * @param direction direction of shortest path from initial state to goal state
     */
    void setDirection(const string &direction);
    /**
    * StringRepresentation method returns the textual representation of solution
    * which print out on screen and stored in file.
    * @return returns the textual representation of solution
    */
    virtual string StringRepresentation() const;
    /**
     * provide a format for textual representation of solution in file
     * @return returns file representation of this solution.
     */
    virtual string fileRepresentation() const;
    /**
     * readSolution method gets input stream object and reads
     * the solution for it.
     * @param is input stream object
     */
    virtual void readSolution(istream& is);
    /**
    * make searcher solution streamable
    * and provide a format for read the object from a text stream
    * @param is input stream object
    * @param solution specific searcher solution object
    * @return return input stream for chaining.
    */
    friend istream &operator>>(istream &is, SearcherSolution **solution);
    /**
     * make solution object streamable.
     * and provide a format for writing the object to a text stream.
     * @param os output stream object
     * @param solution specific solution
     * @return returns output stream for chaining.
     */
    friend ostream &operator<<(ostream &os, SearcherSolution *solution);

};




#endif //PROJECT2_SEARCHERSOLUTION_H
