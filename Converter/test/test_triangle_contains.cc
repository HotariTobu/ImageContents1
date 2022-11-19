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
            assert(!triangle->Contains(&point));
        }
        
        for (int y = 101; y <= 300; y++) {
            Point3d point;
            point.x = x;
            point.y = y;
            assert(!triangle->Contains(&point));
        }
    }

    for (int y = 0; y < 100; y++) {
        for (int x = -200; x < 0; x++) {
            Point3d point;
            point.x = x;
            point.y = y;
            assert(!triangle->Contains(&point));
        }

        for (int x = 101; x <= 300; x++) {
            Point3d point;
            point.x = x;
            point.y = y;
            assert(!triangle->Contains(&point));
        }
    }

    for (int x = 0; x <= 100; x++) {
        for (int y = 0; y <= 100 - x; y++) {
            Point3d point;
            point.x = x;
            point.y = y;
            assert(triangle->Contains(&point));
        }
        
        for (int y = 100 - x + 1; y <= 100; y++) {
            Point3d point;
            point.x = x;
            point.y = y;
            assert(!triangle->Contains(&point));
        }
    }
}