// Created by 

#include <cassert>

#include "../include/normal_vector_getter.h"

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

#ifdef __4_EDGE
// 4-edge code is hear...

    assert(GetNormalVectorIn({
        {nan,   3, nan},
        {  6,   2,   4},
        {nan,   1, nan},
    }) == {-1, 1, -1});

    assert(GetNormalVectorIn({
        {nan,   3, nan},
        {  6,   2, nan},
        {nan,   1, nan},
    }) == {-4, 1, -1});

#elif __8_EDGE
// 8-edge code is hear...

    assert(GetNormalVectorIn({
        {  5,   3,   2},
        {  6,   2,   4},
        {  4,   1,   7},
    }) == {-0.5, 0, -1});

    assert(GetNormalVectorIn({
        {  5,   3,   2},
        {  6,   2, nan},
        {  4,   1,   7},
    }) == {-1, 0.625, -0.75});

#endif
}