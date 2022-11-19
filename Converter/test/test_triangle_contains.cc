// Created by HotariTobu

#include <cassert>

#include "../include/triangle.h"

int main() {
    Point3d point0 = {0, 0, 0};
    Point3d point1 = {100, 0, 0};
    Point3d point2 = {0, 100, 0};

    auto triangle = std::make_shared<Triangle>(&point0, &point1, &point2);

    for (int x = -200; x <= 300; x++) {
        for (int y = -200; y < 0; y++) {
            
        }
        
    }
    

    for (double x = 0.1; x < 3; x += 0.1) {
        Point3d p = {x, 0.1, Rand()};
        assert(r1->Contains(&p));
    }

    for (double y = 0.1; y < 3; y += 0.1) {
        Point3d p = {0.1, y, Rand()};
        assert(r1->Contains(&p));
    }

    for (double x = 0.1, y = 2.9; x < 3 && y > 0; x += 0.1, y -= 0.1) {
        Point3d p = {x, y, Rand()};
        assert(r1->Contains(&p));
    }
}