//
// Created by omri on 09/01/19.
//

#ifndef PROJECT2_MYPRIORITYQUEUE_H
#define PROJECT2_MYPRIORITYQUEUE_H

#include "queue"

using namespace std;
template <typename  T>
class MyPriorityQueue : public priority_queue<T, std::vector<T>> {
public:

    bool remove(const T& value);
};


#endif //PROJECT2_MYPRIORITYQUEUE_H
