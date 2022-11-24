// Created by HotariTobu

#include <array>
#include <cassert>
#include <limits>

#include "../include/normal_vector_getter.h"

bool CanPass(const std::array<double, 9>& neighbor_z_values, Vector3d answer) {
    std::array<ReducerAttribute, 9> raw_neighbor_attributes;
    for (int i = 0; i < 9; ++i) {
        ReducerAttribute attribute;
        attribute.z = neighbor_z_values[i];
        raw_neighbor_attributes[i] = attribute;
    }
    
    std::array<const ReducerAttribute*, 9> neighbor_attributes_ref;
    for (int i = 0; i < 9; ++i) {
        neighbor_attributes_ref[i] = &raw_neighbor_attributes[i];
    }

    Neighbor<ReducerAttribute> neighbor(3);
    neighbor.head = &neighbor_attributes_ref[4];

    auto result = GetNormalVectorIn(neighbor);
    answer.Normalize();

    return Near(result, answer);
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

    assert(CanPass({
        nan,   3, nan,
          6,   2,   4,
        nan,   1, nan,
    }, {1, 1, 1}));

    assert(CanPass({
        nan,   3, nan,
          6,   2, nan,
        nan,   1, nan,
    }, {4, 1, 1}));

    assert(CanPass({
          0,   3,   9,
          6,   2,   4,
          5,   1, nan,
    }, {1, 1, 1}));

    assert(CanPass({
        nan,   3,   3,
          6,   2, nan,
        nan,   1,  15,
    }, {4, 1, 1}));

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

    assert(CanPass({
          5,   3,   2,
          6,   2,   4,
          4,   1,   7,
    }, {0.5, 0, 1}));

    assert(CanPass({
          5,   3,   2,
          6,   2, nan,
          4,   1,   7,
    }, {1, 0.625, 0.75}));

#endif
}