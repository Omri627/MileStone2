#ifndef PROJECT2_CMPPAIRPTRS_H
#define PROJECT2_CMPPAIRPTRS_H

#include <utility>

using namespace std;
template <class T, class S>
class CmpPairPtrs {
public:
    /**
     * compare between pair that contain pointer in container, T must have getCost()
     * @param lhs first obj
     * @param rhs second obj
     * @return bool
     */
    bool operator()(const pair<T,S> lhs, const pair<T,S> rhs) const
    {
        return (lhs.first->getCost() + lhs.second)  > (rhs.first->getCost() + rhs.second);
    }
};


#endif