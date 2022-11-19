// Created by HotariTobu

#include <cassert>
#include <limits>

#include "../include/maps_combiner.h"

bool CanPass(Map2d<double> map1, Map2d<double> map2, Map2d<double> answer) {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    auto result = CombineMaps({
        {map1, PointType::NONE},
        {map2, PointType::NONE},
    });
    
    Map2d<double> result2;
    result2.x = result.x;
    result2.y = result.y;
    result2.width = result.width;
    result2.height = result.height;
    result2.data = std::vector<std::vector<double>>(result.height + 2, std::vector<double>(result.width + 2, nan));
    for (int y = 1; y <= result.height; y++) {
        for (int x = 1; x <= result.height; x++) {
            result2.data[y][x] = result.data[y][x].first;
        }
    }

    return result2 == answer;
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