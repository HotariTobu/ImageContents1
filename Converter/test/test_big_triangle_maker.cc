// Created by 

#include <cassert>

#include "../include/big_triangle_maker.h"

#include "../include/triangle.h"

bool CanPass(PointSet points) {
    auto [p0, p1, p2] = MakeBigTriangle(points);
    Triangle triangle(&p0, &p1, &p2);

    Circle incircle = triangle.GetIncircle();

    for (Point3d point : points) {
        if ((point - incircle.center).Length() > incircle.radius) {
            return false;
        }
    }

    return true;
}

int main() {
    assert(CanPass({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    }));
}