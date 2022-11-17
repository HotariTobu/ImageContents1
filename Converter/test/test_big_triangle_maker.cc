// Created by 

#include <cassert>
#include <ctime>

#include "../include/big_triangle_maker.h"

#include "../include/triangle.h"

bool CanPass() {
    constexpr int points_count = 20;
    PointSet points(points_count);

    for (int i = 0; i < points_count; i++) {
        points[i] = {
            rand(),
            rand(),
            rand(),
        };
    }

    auto [p0, p1, p2] = MakeBigTriangle(points);
    Triangle triangle(&p0, &p1, &p2);

    for (Point3d point : points) {
        if (!triangle->Contains(point)) {
            return false;
        }
    }

    return true;
}

int main() {
    srand(std::time(NULL));

    for (int i = 0; i < 5; ++i) {
        assert(CanPass());
    }
}