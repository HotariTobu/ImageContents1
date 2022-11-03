// Created by 

#include <cassert>

#include "../include/randomizer.h"

bool CanPass() {
    PointSet points;

    for (int i = 0; i < 10; i++) {
        Point3d point;
        point.x = rand();
        point.y = rand();
        point.z = rand();
        points.push_back(point);
    }
    
    Point3d clone = std::copy(points);

    Randomize(clone);

    return points != clone;
}

int main() {
    srand(time(NULL));

    assert(CanPass());
    assert(CanPass());
    assert(CanPass());
}