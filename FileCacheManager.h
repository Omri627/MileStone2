#ifndef FILE_CACHE_MANAGER
    #define FILE_CACHE_MANAGER

#include <string>
#include <fstream>
#include "CmpMazeGame.h"
#include "CacheManager.h"
pthread_mutex_t global_mutex;
using namespace std;

template <class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    /* map linked between specific problems and their solutions */
    map<Problem, Solution, CmpMazeGame<Problem> > solutions;
    /* url of file that store the data */
    string fileUrl;
    /**
     * getStartIterator method returns iterator for the begin.
     * @return returns iterator for the begin.
     */
    typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator getStartIterator() {
        return this->solutions.begin();
    }
    /**
     * getEndIterator method returns iterator for the end.
     * @return returns iterator for the end.
     */
    typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator getEndIterator() {
        return this->solutions.end();
    }
    /**
     * loadMap method loads the problems and their solution that already solved
     * and stored in file.
     */
    void loadMap () {
        Problem problem;                 // specific instance of problem
        Solution solution;               // stored solution for problem
        string delimiter;                // delimiter buffer
        ifstream file;                   // input stream of file

        /* open data file */
        file.open(this->fileUrl);

        /* if case file doest exist */
        if (!file)
            return;
        pthread_mutex_lock(&global_mutex);
        /* load instances of problem one by one and store in cache object */
        while (file >> &problem) {
            file >> delimiter;          // ignore delimiter between problem and solution
            file >> &solution;           // load solution for problem
            this->storeSolution(problem, solution);
        }
        pthread_mutex_unlock(&global_mutex);

        /* close file */
        file.close();

    }
    /**
     * save all stored problems, and their solutions that already computed.
     * in file.
     */
    void saveData() {
        ofstream file;                          // output file stream
        file.open(this->fileUrl);               // open file.
        typename map < Problem, Solution, CmpMazeGame<Problem> >::iterator iterator;
        iterator = this->solutions.begin();
        /* run through all pairs of problems and solutions that has been computed
         * and stored them in file. */
        pthread_mutex_lock(&global_mutex);
        while (iterator != this->solutions.end()) {
            file << *iterator->first << "$" << endl << iterator->second;
            iterator++;
        }
        pthread_mutex_unlock(&global_mutex);
        /*  close file*/
        file.close();
    }
public:
    /**
     * creates a file cache manager object initialized with file url path.
     * the chache is using extern memory to store the data.
     * @param fileUrl url of file.
     */
    FileCacheManager(string fileUrl) {
        this->fileUrl = fileUrl;
        this->loadMap();
    }
    /**
     * isSolutionExist method checks whether there is solution stored in chache
     * for given problem
     * @param problem specific problem
     * @return returns true if problem already solved and his solution stored in memory
     * at any other case returns false
     */
    virtual bool isSolutionExist(const Problem problem) {
        typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator iterator;
        iterator = this->solutions.find(problem);
        if (iterator == this->solutions.end())
            return false;
        return true;
    }
    /**
     * getSolution method gets a problem and returns his value.
     * assumption: the problem's solution stored in chache.
     * @param problem specific problem.
     * @return returns the solution for given instance of problem,
     */
    virtual Solution getSolution(Problem problem) {
        return this->solutions[problem];
    }
    /**
     * storeSolution method gets a problem and solution.
     * and stored them in cache.
     * @param problem instance of problem
     * @param solution solution for this problem
     */
    virtual void storeSolution(Problem problem, Solution solution) {
        this->solutions[problem] = solution;
    }
    /**
     * destrcutor, used to free memory.
     */
    virtual ~FileCacheManager() {
        this->saveData();
        typename map<Problem, Solution, CmpMazeGame<Problem>>::iterator it;
        for (it = this->solutions.begin(); it != this->solutions.end() ; it++) {
            if (it->first != nullptr) {
                delete it->first;
            }
            if (it->second != nullptr) {
                delete it->second;
            }
            this->solutions.erase(it);
        }
    }



};
#endif
