#ifndef PROJECT2_PAIRPRIORITYQUEUE_H
#define PROJECT2_PAIRPRIORITYQUEUE_H

#include <queue>
#include <algorithm>
#include "CmpPairPtrs.h"

template <typename  T, typename S>
class PairPriorityQueue : public priority_queue<pair<T,S>, std::vector<pair<T,S>>, CmpPairPtrs<T,S>> {

public:

    bool remove(const pair<T,S>& value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }
};

#endif //PROJECT2_PAIRPRIORITYQUEUE_H
