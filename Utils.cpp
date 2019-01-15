//
// Created by ranraboh on 11/01/19.
//
#include "Server.h"
#include "Utils.h"
/**
* isValidMatrixRow method gets input row and number of elements that should be in row.
* the method check if row is valid and consist right amount of elements
* @param row row of input
* @param elements number of elements in row
* @return return true if given row is valid
* otherwise return false
*/
bool Utils::isValidMatrixRow(string row, int elements) {
    unsigned long commas = 0;
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == ',')
            commas++;
        if (!isNumber(row[i]) && row[i] != ',')
            return false;
    }
    return (commas == elements)? true : false;
}
/**
 * isNumber method gets a character
 * and return a bool variable indicating whether this character is number or not.
 * @param ch given character
 * @return return true if given character is digit
 * otherwise return false
 */
bool Utils::isNumber(char ch) {
    if ((ch >= '0' && ch <= '9') || ch == '.')
        return true;
    return false;
}
/**
 * isNumber method gets a string and return a boolean variable indicating
 * whether given string contains numeric data or not.
 * @param str given string
 * @return return true if given string is numeric
 * at any other case returns false
 */
bool Utils::isNumber(string str) {
    for (int i = 0; i < str.size(); i++)
        if (!isNumber(str[i]))
            return false;
    return true;
}
/**
 * count the number of commas in given string
 * @param str specific string
 * @return returns the amount of commas in given string.
 */
int Utils::commansAmount(string str) {
    int commas = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',')
            commas++;
    }
    return commas;
}