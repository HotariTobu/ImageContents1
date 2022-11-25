// Created by HotariTobu

#include <array>
#include <cassert>
#include <cmath>
#include <limits>

#include "../include/calculator.h"

bool CanPass(const std::array<double, 9>& z_values, double answer) {
    std::array<const double*, 9> z_values_ref;
    for (int i = 0; i < 9; i++) {
        if (std::isnan(z_values[i])) {
            z_values_ref[i] = nullptr;
        }
        else {
            z_values_ref[i] = &z_values[i];
        }
    }

    Neighbor<double> neighbor(3);
    neighbor.head = &z_values_ref[4];

    double result = Calculate(neighbor);

    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

#ifdef __MIN
// Min code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 2));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 2));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 2));

#elif __MAX
// Max code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 8));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 8));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 6));

#elif __MEAN
// Mean code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 5));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 5));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 4));

#elif __MEDIAN
// Median code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 5));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 5));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 4));

#endif

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

#ifdef __MIN
// Min code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 1));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 1));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 2));

#elif __MAX
// Max code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 9));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 9));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 7));

#elif __MEAN
// Mean code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 5));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 5));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 4.4));

#elif __MEDIAN
// Median code is hear...

    assert(CanPass({
        1,   2, 3,
        4, nan, 6,
        7,   8, 9,
    }, 5));

    assert(CanPass({
          1,   2, nan,
        nan, nan, nan,
        nan,   8,   9,
    }, 5));

    assert(CanPass({
        nan,   2,   3,
          4, nan,   6,
          7, nan, nan,
    }, 4));

#endif

#endif
}