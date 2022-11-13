// Created by 

#include <cassert>
#include <limits>

#include "../include/calculator.h"

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

#ifdef __MIN
// Min code is hear...

    assert(Calculate({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }) == 1);

    assert(Calculate({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }) == 1);

    assert(Calculate({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }) == 2);

#elif __MAX
// Max code is hear...

    assert(Calculate({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }) == 9);

    assert(Calculate({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }) == 9);

    assert(Calculate({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }) == 7);

#elif __MEAN
// Mean code is hear...

    assert(Calculate({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }) == 5);

    assert(Calculate({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }) == 5);

    assert(Calculate({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }) == 4.4);

#elif __MEDIAN
// Median code is hear...

    assert(Calculate({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }) == 5);

    assert(Calculate({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }) == 5);

    assert(Calculate({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }) == 4);

#endif
}