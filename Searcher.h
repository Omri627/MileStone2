
#ifndef PROJECT2_SEARCHER_H
    #define PROJECT2_SEARCHER_H

#include "Searchable.h"
#include "vector"
#include "Solution.h"

#define RIGHT "Right"
#define LEFT "Left"
#define DOWN "Down"
#define UP "Up"

using namespace std;
template <class T>
class Searcher {
private:
    string checkDirection(State<T>* prev, State<T>* curr) {
        string dir;
        if (curr->getRow() < prev->getRow()) {
            dir = UP;
        } else if (curr->getRow() > prev->getRow()) {
            dir = DOWN;
        } else if (curr->getColumn() < prev->getColumn()) {
            dir = LEFT;
        } else {
            dir = RIGHT;
        }
        return dir;
    }

    string getDirectionFromVector(vector<string> vec) {
        string res;
        for (std::vector<string>::iterator it = vec.begin(); it != vec.end(); ++it ) {
            res += *it;
            res+= ", ";
        }
        if (!res.empty())
            res = res.substr(0, res.length() -2);
        return res;
    }


protected:
    void relax(State<T>* from, State<T> * to) {
        if (to->getCost() > from->getCost() + to->getState() || to->getCost() == -1) {
            to->setCost(from->getCost() + to->getState());
            to->setCameFrom(from);
        }
    }
    virtual double getCostOfPath(State<T>* start, State<T>* end) {
        double sum = 0;
        State<T>* temp= end;
        while (temp != start) {
            sum += temp->getState();
            temp = temp->getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }
        }
        return sum;
    }

    virtual double getLengthOfPath(State<T>* start, State<T>* end) {
        double counter = 0;
        State<T>* temp = end;
        while (temp != start) {
            counter += 1;
            temp = temp->getCameFrom();
            if (temp == nullptr) {
                //there is no path
                return -1;
            }

        }
        return counter;
    }

    virtual string getDirection(State<T>* start, State<T>* end) {
        vector<string> directions;
        string result;
        State<T>* temp = end;
        while (temp != start) {
            result = checkDirection(temp->getCameFrom(), temp);
            directions.insert(directions.begin(),result);
            temp = temp->getCameFrom();
        }
        return getDirectionFromVector(directions);
    }

    virtual int getDevelopStates(list<State<T>*> states) {
        int develops = 0;
        for (State<T>* state : states) {
            if (state->getColor() == GRAY || state->getColor() == BLACK)
                develops++;
        }
        return develops;
    }


public:
    virtual SearcherSolution *search(Searchable<T> *searchable) = 0;




};
#endif //PROJECT2_SEARCHER_H
