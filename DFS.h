//
// Created by omri on 07/01/19.
//

#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#import "Searcher.h"
template <class Solution, class State>
class DFS : public Searcher<Solution, State>{

public:
    Solution search(Searchable<State> searchable);
};


#endif //PROJECT2_DFS_H
