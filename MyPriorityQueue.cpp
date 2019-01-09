//
// Created by omri on 09/01/19.
//

#include <algorithm>
#include "MyPriorityQueue.h"
template <typename  T>
bool MyPriorityQueue<T>::remove(const T &value) {
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