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
            Point3d point;
            point.x = x;
            point.y = y;
            assert(triangle->Contains(&point));
        }
        
    }

}