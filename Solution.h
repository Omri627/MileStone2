#ifndef PROJECT2_SOLUTION_H
#define PROJECT2_SOLUTION_H

#include <string>
using namespace std;
class Solution {
public:
    virtual string StringRepresentation() const = 0 ;

    virtual void readSolution(istream& is) = 0;

    friend istream &operator>>(istream &is, Solution * solution) {
        solution->readSolution(is);
        return is;
    }
    friend ostream &operator<<(ostream &os, Solution const * solution) {
        os << solution->StringRepresentation() << endl;
        return os;
    }
};


#endif //PROJECT2_SOLUTION_H