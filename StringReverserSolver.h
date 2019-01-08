#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H

#include <string>
#include "Solver.h"
using namespace std;
class StringReverserSolver : public Solver<string, string>  {
public:
    virtual string solve(string problem);

private:
    string reverseString(string s);

public:
    virtual ~StringReverserSolver();
};
#endif