#include "StringReverser.h"
StringReverser::StringReverser(string problem, string solution)
: Solver(problem, solution) {

}

string StringReverser::solve(string problem) {

}


string StringReverser::reverseString(string str) {
        int n = str.length();

        // Swap character starting from two
        // corners
        for (int i = 0; i < n / 2; i++) {
            swap(str[i], str[n - i - 1]);
        }

        return str;
}
