// Created by 

#include <cassert>
#include <limits>

#include "../include/simulator.h"

extern double simulator_threshold;

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    simulator_threshold = 2;

    double value = 12;

    Neighbor n1, n2;
    assert(n1 == n2);

#ifdef __UNIFORM
// Uniform code is hear...

#ifdef __4_NEIGHBOR
// Uniform 4-neighbor code is hear...

    assert(
        Simulate(
            3,
            {
                {    0, 4, -3.14},
                { 6.66, 5,    54},
                {0.001, 1,  -5.8},
            }
        ) == Neighbor({
            {0, 1, 0},
            {1, 0, 0},
            {0, 1, 0},
        })
    );

#elif __8_NEIGHBOR
// Uniform 8-neighbor code is hear...

    assert(
        Simulate(
            7,
            {
                {    0, 4, -3.14},
                { 6.66, 5,    54},
                {0.001, 1,  -5.8},
            }
        ) == Neighbor({
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
        })
    );

#endif

#elif __FLEXIBLE
// Flexible code is hear...

#ifdef __4_NEIGHBOR
// Flexible 4-neighbor code is hear...

#elif __8_NEIGHBOR
// Flexible 8-neighbor code is hear...

#endif

#endif
}