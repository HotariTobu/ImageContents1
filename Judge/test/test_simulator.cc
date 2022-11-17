// Created by HotariTobu

#include <cassert>
#include <limits>

#include "../include/simulator.h"

extern double simulator_threshold;

bool CanPass(double value, Neighbor neighbor, Neighbor answer) {
    return Simulate(value, neighbor) == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    simulator_threshold = 2;

#ifdef __UNIFORM
// Uniform code is hear...

#ifdef __4_NEIGHBOR
// Uniform 4-neighbor code is hear...

    assert(CanPass(
        3,
        {
                0, 4, -3.14,
             6.66, 5,    54,
            0.001, 1,  -5.8,
        },
        {
            0, 1, 0,
            1, 0, 0,
            0, 1, 0,
        }
    ));

#elif __8_NEIGHBOR
// Uniform 8-neighbor code is hear...

    assert(CanPass(
        7,
        {
                0, 4, -3.14,
             6.66, 5,    54,
            0.001, 1,  -5.8,
        },
        {
            1, 1, 1,
            1, 0, 0,
            1, 1, 1,
        }
    ));

#endif

#elif __FLEXIBLE
// Flexible code is hear...

#ifdef __4_NEIGHBOR
// Flexible 4-neighbor code is hear...

    assert(CanPass(
        4,
        {
             76,  11,   9,
             11,  10,  74,
              2,  10,  13,
        },
        {
              0,   1,   0,
              1,   0,   0,
              0,   2,   0,
        }
    ));

#elif __8_NEIGHBOR
// Flexible 8-neighbor code is hear...

    assert(CanPass(
        44,
        {
             76,  11,   9,
             11,  10,  74,
              2,  10,  13,
        },
        {
              0,  10,  10,
             10,   0,   0,
              3,  11,   0,
        }
    ));

#endif

#endif
}