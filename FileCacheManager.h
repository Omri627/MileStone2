#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H

#include <string>
#include "CacheManager.h"
using namespace std;
class FileCacheManager : public CacheManager {
    string fileUrl;

    bool isSolutionExist(P problem) override;

    S *getSolution(P problem) override;

    void storeSolution(P p, S s) override;
};


#endif //PROJECT2_FILECACHEMANAGER_H
