
#ifndef PROJECT2_SEARCHER_H
    #define PROJECT2_SEARCHER_H

#include "Solution.h"
#include "Searchable.h"
#include "vector"
#include "State.h"
#include "string"
#include "SearcherSolution.h"

#define RIGHT "Right"
#define LEFT "Left"
#define DOWN "Down"
#define UP "Up"

using namespace std;
template <class T>
class Searcher {
private:
    //todo: write documantation
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
    // todo : write documantation
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
    /**
     * relax method correct the cost of destination state when found lower-cost route.
     * the idea is to repeatedly improve estimates	toward	goal
     * @param from source node
     * @param to destionation node
     */
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
    /**
     * compute the length of shortest path from start node to end node
     * using the computations of searcher algorith.
     * @param start
     * @param end
     * @return returns the length of minimal path from start state to end state.
     */
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
    /**
     * getDirection method computes the direction from source node
     * to destination node of shortest path in graph.
     * @param start source node
     * @param end destination node.
     * @return string described the directions from start node to end node.
     */
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
    // todo: write documantation
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
