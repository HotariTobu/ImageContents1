// Created by HotariTobu

#include <cassert>
#include <limits>

#include "../include/maps_combiner.h"

bool CanPass(Map2d<double> map1, Map2d<double> map2, Map2d<double> answer) {
    std::vector<Map2d<double>> maps = {map1, map2};
    auto result = CombineMaps(maps);
    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    assert(
        CanPass({
            0 ,0 ,3 ,3,
            {
                {nan, nan, nan, nan, nan},
                {nan,   1,   2, nan, nan},
                {nan,   4, nan, nan, nan},
                {nan,   7,   8, nan, nan},
                {nan, nan, nan, nan, nan},
            }
        },
        {
            0 ,0 ,3 ,3,
            {
                {nan, nan, nan, nan, nan},
                {nan, nan, nan,   3, nan},
                {nan,  10,   5,   6, nan},
                {nan, nan, nan,   9, nan},
                {nan, nan, nan, nan, nan},
            }
        },
        {
            0, 0, 3, 3,
            {
                {nan, nan, nan, nan, nan},
                {nan,   1,   2,   3, nan},
                {nan,  10,   5,   6, nan},
                {nan,   7,   8,   9, nan},
                {nan, nan, nan, nan, nan},
            }
        })
    );
}