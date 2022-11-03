// Created by 

#include <cassert>

#include "../include/maps_combiner.h"

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    assert(
        CombineMaps({
            {
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
        }) == Map2d(
            {
                0, 0, 3, 3,
                {
                    {nan, nan, nan, nan, nan},
                    {nan,   1,   2,   3, nan},
                    {nan,   4,   5,   6, nan},
                    {nan,   7,   8,   9, nan},
                    {nan, nan, nan, nan, nan},
                }
            }
        )
    );
}