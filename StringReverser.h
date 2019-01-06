//
// Created by ranraboh on 06/01/19.
//

#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H


#include <string>
#include "Solver.h"
using namespace std;
class StringReverser : public Solver<string, string>  {
public:
    StringReverser(string problem, string solution);

    virtual string solve(string problem);

private:
    string reverseString(string s);
};


#endif