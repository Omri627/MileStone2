//
// Created by ranraboh on 11/01/19.
//
#include "Server.h"
#include "Utils.h"
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
bool Utils::isNumber(char ch) {
    if ((ch >= '0' && ch <= '9') || ch == '.')
        return true;
    return false;
}
bool Utils::isNumber(string str) {
    for (int i = 0; i < str.size(); i++)
        if (!isNumber(str[i]))
            return false;
    return true;
}