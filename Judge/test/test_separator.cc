// Created by 

#include <cassert>

#include "../include/separator.h"

extern double separator_threshold;

std::pair<Map2d<double>, Map2d<double>> pack(Map2d<double> map1, Map2d<double> map2) {
    return std::make_pair(map1, map2);
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    separator_threshold = 2;
    
    assert(
        Separate({
            0, 0, 3, 3,
            {
                {{nan, nan}, {nan, nan}, {nan, nan}, {nan, nan}, {nan, nan}},
                {{nan, nan}, {-56,   5}, { 20, 2.1}, {1.2,   0}, {nan, nan}},
                {{nan, nan}, { -5, 1.9}, { -9,   2}, {  2,   3}, {nan, nan}},
                {{nan, nan}, {2.7, 0.6}, { 30,   3}, {100,   1}, {nan, nan}},
                {{nan, nan}, {nan, nan}, {nan, nan}, {nan, nan}, {nan, nan}},
            }
        }) == pack(
            {
                0, 0, 3, 3,
                {
                    {nan, nan, nan, nan, nan},
                    {nan, -56,  20, nan, nan},
                    {nan, nan, nan,   2, nan},
                    {nan, nan,  30, nan, nan},
                    {nan, nan, nan, nan, nan},
                }
            },
            {
                0, 0, 3, 3,
                {
                    {nan, nan, nan, nan, nan},
                    {nan, nan, nan, 1.2, nan},
                    {nan,  -5,  -9, nan, nan},
                    {nan, 2.7, nan, 100, nan},
                    {nan, nan, nan, nan, nan},
                }
            }
        )
    );
}