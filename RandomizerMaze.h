
#ifndef PROJECT2_RANDOMIZEMAZE_H
#define PROJECT2_RANDOMIZEMAZE_H

#include "MazeGame.h"
using namespace std;
class RandomizerMaze {
private:
    int size, start ,end;
    std::default_random_engine generator;

    string getRandomRow() {
        random_device rand_dev;
        mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distribution(start,end);
        string row = "";
        for (int i = 0; i < size - 1; ++i) {

            int dice_roll = distribution(generator);
            row += to_string(dice_roll);
            row += ",";
        }
        row += to_string(distribution(generator));
        return row;
    }
public:

    RandomizerMaze (int matrixSize, int start, int end) {
        this->size = matrixSize;
        this->start = start;
        this->end = end;
    }

    MazeGame<int>* getRandomMaze() {
        vector<string> matrix;
        matrix.push_back("0,0");
        string endPoint = to_string(size - 1);
        endPoint+= ",";
        endPoint += to_string(size - 1);
        matrix.push_back(endPoint);
        for (int i = 0; i < size ; ++i) {
            matrix.push_back(getRandomRow());
        }
        return new MazeGame<int>(matrix);
    }

    static vector<string> readMatrix(istream &file) {
        vector<string> mat;
        int size = 0;
        file >> size;
        string line;
        for (int i = 0; i < size + 2 ; ++i) {
             string line;
             file >> line;
             mat.push_back(line);
            /*getline(file,line);
            if (i > 0) {
               line = line.substr(0, line.length()-1);
               mat.push_back(line);
           }*/

        }

        return mat;
    }




};


#endif //PROJECT2_RANDOMIZEMAZE_H
