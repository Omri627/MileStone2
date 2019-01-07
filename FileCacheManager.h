#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H

#include <string>
#include "CacheManager.h"
using namespace std;
template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    string fileUrl;
public:
    FileCacheManager(string fileUrl);

    void loadMap();

    void saveData();

};


#endif