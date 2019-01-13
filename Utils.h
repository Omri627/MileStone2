//
// Created by ranraboh on 11/01/19.
//

#ifndef PROJECT2_UTILS_H
#define PROJECT2_UTILS_H

#include <string>
using namespace std;
class Utils {
public:
    /**
     * isValidMatrixRow method gets input row and number of elements that should be in row.
     * the method check if row is valid and consist right amount of elements
     * @param row row of input
     * @param elements number of elements in row
     * @return return true if given row is valid
     * otherwise return false
     */
    static bool isValidMatrixRow(string row, int elements);
    /**
     * isNumber method gets a character
     * and return a bool variable indicating whether this character is number or not.
     * @param ch given character
     * @return return true if given character is digit
     * otherwise return false
     */
    static bool isNumber(char ch);
    /**
     * isNumber method gets a string and return a boolean variable indicating
     * whether given string contains numeric data or not.
     * @param str given string
     * @return return true if given string is numeric
     * at any other case returns false
     */
    static bool isNumber(string str);
};


#endif //PROJECT2_UTILS_H
