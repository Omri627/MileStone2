#ifndef PROJECT2_MYPRIORITYQUEUE_H
#define PROJECT2_MYPRIORITYQUEUE_H

#include "queue"

using namespace std;
template <typename  T>
class MyPriorityQueue : public priority_queue<T, std::vector<T>, std::greater<T>> {
    //priority queue that use greater instead of less operator
    //todo:: if the priority queue is not reverse so I need to change the less operator to >
public:

    bool remove(const T& value);
};


#endif //PROJECT2_MYPRIORITYQUEUE_H
