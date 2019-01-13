#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H

#include <string>
#include "Solver.h"
using namespace std;
class StringReverserSolver : public Solver<string, string>  {
public:
    /**
    * solve method get specific instance of problem and solve it.
    * i.e gets a string and causes this character sequence to be replaced by the reverse of the sequence.
    * @param problem specific problem
    * @return return reverse string of given parameter.
    */
    virtual string solve(string problem);

private:
    /**
    * reverseString method causes this character sequence to be replaced by the reverse of the sequence.
    * @param str specific string.
    * @return reversed content of given string
    */
    string reverseString(string s);

public:
    /**
    * free, used to deallocate memory
    */
    virtual ~StringReverserSolver();
};
#endif