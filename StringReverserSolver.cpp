#include "StringReverserSolver.h"
StringReverserSolver::StringReverserSolver(string problem, string solution)
: Solver(problem, solution) {

}

string StringReverserSolver::solve(string problem) {
    return this->reverseString(problem);
}
string StringReverserSolver::reverseString(string str) {
        int n = str.length();

        // Swap character starting from two
        // corners
        for (int i = 0; i < n / 2; i++) {
            swap(str[i], str[n - i - 1]);
        }

        return str;
}