#include "StringReverserSolver.h"
/**
 * solve method get specific instance of problem and solve it.
 * i.e gets a string and causes this character sequence to be replaced by the reverse of the sequence.
 * @param problem specific problem
 * @return return reverse string of given parameter.
 */
string StringReverserSolver::solve(string problem) {
    return this->reverseString(problem);
}
/**
 * reverseString method causes this character sequence to be replaced by the reverse of the sequence.
 * @param str specific string.
 * @return reversed content of given string
 */
string StringReverserSolver::reverseString(string str) {
        int n = str.length();

        // Swap character starting from two
        // corners
        for (int i = 0; i < n / 2; i++) {
            swap(str[i], str[n - i - 1]);
        }

        return str;
}
/**
 * free, used to deallocate memory
 */
StringReverserSolver::~StringReverserSolver() {

}
