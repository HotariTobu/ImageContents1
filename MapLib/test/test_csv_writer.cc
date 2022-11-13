// Created by 

#include <cassert>
#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>

#include "csv_writer.h"

bool CanPass(Map2d<double> map, const char* answer) {
    const char* filename = "test.csv";

    WriteCSV(filename, map);

    std::ifstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    std::string result = buffer.str();

    std::filesystem::remove(filename);

    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();
    
    assert(CanPass(
        {
            1, -5, 3, 3,
            {
                {nan, nan, nan, nan, nan},
                {nan,   0,   4, -31, nan},
                {nan, 6.6, nan,  54, nan},
                {nan, nan,   1,  -5, nan},
                {nan, nan, nan, nan, nan},
            }
        },
        R"(1,4,-5,-2
0,4,-31
6.6,NaN,54
NaN,1,-5)"
    ));
}