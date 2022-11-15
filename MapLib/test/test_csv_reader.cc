// Created by 

#include <cassert>
#include <filesystem>
#include <fstream>
#include <limits>

#include "csv_reader.h"

bool CanPass(const char* data, Map2d<double> answer) {
    const char* filename = "test.csv";
    
    std::ofstream ofs(filename, std::ios::trunc);
    ofs << data;
    ofs.close();

    Map2d<double> result = ReadCSV(filename);

    std::filesystem::remove(filename);

    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    assert(CanPass(
        R"(1,3,-5,-3
0,4,-31
6.6,NaN,54
NaN,1,-5)",
        {
            1, -5, 3, 3,
            {
                {nan, nan, nan, nan, nan},
                {nan,   0,   4, -31, nan},
                {nan, 6.6, nan,  54, nan},
                {nan, nan,   1,  -5, nan},
                {nan, nan, nan, nan, nan},
            }
        }
    ));
}