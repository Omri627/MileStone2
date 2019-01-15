#ifndef PROJECT2_CMPSTATEPTRS_H
#define PROJECT2_CMPSTATEPTRS_H

#include "State.h"
template <class T>
class CmpStatesPtrs{
public:
    /* compare between two state by their cost. */
    bool operator()(const T lhs, const T rhs) const
    {
        return lhs->getCost() > rhs->getCost();
    }
};
#endif //PROJECT2_CMPSTATEPTRS_H
