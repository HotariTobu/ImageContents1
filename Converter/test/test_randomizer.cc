// Created by 

#include <cassert>
#include <ctime>

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
    
    PointSet clone = points;

    Randomize(clone);

    return points != clone;
}

int main() {
    srand(std::time(NULL));

    assert(CanPass());
    assert(CanPass());
    assert(CanPass());
}