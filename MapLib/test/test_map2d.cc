// Created by 

#include <cassert>

#include "map2d.h"

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();
    
    Map2d<double> map1;
    map1.x = 1;
    map1.y = -5;
    map1.width = 3;
    map1.height = 3;
    map1.data = {
        {nan, nan, nan, nan, nan},
        {nan,   0,   4, -31, nan},
        {nan, 6.6, nan,  54, nan},
        {nan, nan,   1,  -5, nan},
        {nan, nan, nan, nan, nan},
    };

    Map2d<double> map2;
    map2.x = 1;
    map2.y = -5;
    map2.width = 3;
    map2.height = 3;
    map2.data = {
        {nan, nan, nan, nan, nan},
        {nan,   0,   4, -31, nan},
        {nan, 6.6, nan,  54, nan},
        {nan, nan,   1,  -5, nan},
        {nan, nan, nan, nan, nan},
    };

    assert(map1 == map2);

    const Map2d<double> map3 = {
            1, -5, 3, 3,
            {
                {nan, nan, nan, nan, nan},
                {nan,   0,   4, -31, nan},
                {nan, 6.6, nan,  54, nan},
                {nan, nan,   1,  -5, nan},
                {nan, nan, nan, nan, nan},
            }
        };

    assert(map1 == map3);

    const Map2d<double> map4 = {
            1, -5, 3, 3,
            {
                {nan, nan, nan, nan, nan},
                {nan,  -9,   4, -31, nan},
                {nan, 6.6, nan,  54, nan},
                {nan, nan,   1,  -5, nan},
                {nan, nan, nan, nan, nan},
            }
        };

    assert(map3 != map4);
}