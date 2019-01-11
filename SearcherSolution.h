#ifndef PROJECT2_SEARCHERSOLUTION_H
#define PROJECT2_SEARCHERSOLUTION_H

#include <ostream>
#include "Solution.h"

class SearcherSolution : public Solution {
private:
    int totalCost;
    int length;
public:
    SearcherSolution(int totalCost, int length);

    int getTotalCost() const;

    int getLength() const;

    void setTotalCost(int totalCost);

    void setLength(int length);

    virtual string StringRepresentation() const;

    virtual void readSolution(istream& is);

    //friend ostream &operator<<(ostream &os, SearcherSolution const*solution);

    friend istream &operator>>(istream &is, SearcherSolution *solution);

};




#endif //PROJECT2_SEARCHERSOLUTION_H
