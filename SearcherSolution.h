#ifndef PROJECT2_SEARCHERSOLUTION_H
#define PROJECT2_SEARCHERSOLUTION_H
#include "Solution.h"

class SearcherSolution : public Solution {
private:
    int totalCost;
    int length;
public:
    SearcherSolution(int totalCost, int length);

    int getTotalCost() const;

    int getLength() const;

    virtual string StringRepresentation();
};


#endif //PROJECT2_SEARCHERSOLUTION_H
