#ifndef PROJECT2_SEARCHERSOLUTION_H
#define PROJECT2_SEARCHERSOLUTION_H

#include "Solution.h"
using namespace std;
class SearcherSolution : public Solution {
private:
    int totalCost;
    int length;
    int developStates;
    string direction;
public:
    SearcherSolution(int totalCost, int length);

    SearcherSolution(int totalCost, int length, int developStates);

    SearcherSolution(int totalCost, int length, int developStates, string direction);

    int getTotalCost() const;

    int getLength() const;

    void setTotalCost(int totalCost);

    void setLength(int length);

    int getDevelopStates() const;

    void setDevelopStates(int developStates);

    const string &getDirection() const;

    void setDirection(const string &direction);

    virtual string StringRepresentation() const;

    virtual void readSolution(istream& is);

    //friend ostream &operator<<(ostream &os, SearcherSolution const*solution);

    friend istream &operator>>(istream &is, SearcherSolution **solution);

};




#endif //PROJECT2_SEARCHERSOLUTION_H
