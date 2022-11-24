// Created by HotariTobu

#include <cassert>
#include <limits>

#include "../include/simulator.h"

extern double simulator_threshold;

bool CanPass(double value, const std::array<double, 9>& neighbor_z_values, const std::array<std::array<double, 3>, 3>& answer) {
    std::array<Attribute, 9> raw_neighbor_attributes;
    for (int i = 0; i < 9; ++i) {
        Attribute attribute;
        attribute.z = neighbor_z_values[i];
        raw_neighbor_attributes[i] = attribute;
    }
    
    std::array<const Attribute*, 9> neighbor_attributes_ref;
    for (int i = 0; i < 9; ++i) {
        neighbor_attributes_ref[i] = &raw_neighbor_attributes[i];
    }

    Neighbor<Attribute> neighbor(3);
    neighbor.head = &neighbor_attributes_ref[4];

    auto result = Simulate(value, neighbor);
    
    return result == answer;
}

int main() {
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