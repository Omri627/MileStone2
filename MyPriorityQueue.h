#ifndef PROJECT2_MYPRIORITYQUEUE_H
#define PROJECT2_MYPRIORITYQUEUE_H

#include <queue>
#include <algorithm>

using namespace std;
template <typename  T>
class MyPriorityQueue : public priority_queue<T, std::vector<T>, std::less<T>> {
    //priority queue that use greater instead of less operator
    //todo:: if the priority queue is not reverse so I need to change the less operator to >
public:

    bool remove(const T& value) {
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


#endif //PROJECT2_MYPRIORITYQUEUE_H
