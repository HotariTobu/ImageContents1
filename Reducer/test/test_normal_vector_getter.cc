// Created by 

#include <cassert>
#include <limits>

#include "../include/normal_vector_getter.h"

bool CanPass(Neighbor neighbor, Vector3d vector) {
    return GetNormalVectorIn(neighbor) == vector;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

    assert(CanPass({
        nan,   3, nan,
          6,   2,   4,
        nan,   1, nan,
    }, {-1, 1, -1}));

    assert(CanPass({
        nan,   3, nan,
          6,   2, nan,
        nan,   1, nan,
    }, {-4, 1, -1}));

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

    assert(CanPass({
          5,   3,   2,
          6,   2,   4,
          4,   1,   7,
    }, {-0.5, 0, -1}));

    assert(CanPass({
          5,   3,   2,
          6,   2, nan,
          4,   1,   7,
    }, {-1, 0.625, -0.75}));

#endif
}