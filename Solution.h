#ifndef PROJECT2_SOLUTION_H
#define PROJECT2_SOLUTION_H

#include <string>
#include <istream>
#include <ostream>

class Solution {
public:
    /**
     * StringRepresentation method returns the textual representation of solution
     * which print out on screen and stored in file.
     * @return returns the textual representation of solution
     */
    virtual std::string StringRepresentation() const = 0 ;
    /**
     * readSolution method gets input stream object and reads
     * the solution for it.
     * @param is input stream.
     */
    virtual void readSolution(std::istream& is) = 0;
    /**
     * make solution streamable
     * and provide a format for read the object from a text stream
     * @param is input stream object
     * @param solution specific solution object
     * @return return input stream for chaining.
     */
    friend std::istream &operator>>(std::istream &is, Solution * solution) {
        solution->readSolution(is);
        return is;
    }
    /**
     * make solution object streamable.
     * and provide a format for writing the object to a text stream.
     * @param os output stream object
     * @param solution specific solution
     * @return returns output stream for chaining.
     */
    friend std::ostream &operator<<(std::ostream &os, Solution const * solution) {
        os << solution->StringRepresentation() << std::endl;
        return os;
    }
};


#endif //PROJECT2_SOLUTION_H