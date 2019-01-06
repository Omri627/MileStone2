#ifndef PROJECT2_CACHEMANAGER_H
#define PROJECT2_CACHEMANAGER_H
template <class P, class S>
class CacheManager {
    virtual bool isSolutionExist(P problem);
    virtual S* getSolution(P problem);
    virtual void storeSolution(P p, S s);
};


#endif