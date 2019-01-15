#ifndef PROJECT2_CMPMAZEGAME_H
    #define PROJECT2_CMPMAZEGAME_H

template <class T>
class CmpMazeGame {
public:
    /* compare between two maze game objects */
    bool operator()(const T lhs, const T rhs) const {
        return *lhs < *rhs;
    }
};

#endif