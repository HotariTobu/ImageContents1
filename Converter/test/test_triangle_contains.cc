// Created by HotariTobu

#include <cassert>

#include "../include/triangle.h"

IndexedPoint2d MakePoint(double x, double y) {
    static int index = 0;
    auto raw_point = new Point2d;
    raw_point->x = x;
    raw_point->y = y;
    return {index++, raw_point};
}

int main() {
    auto point0 = MakePoint(0, 0);
    auto point1 = MakePoint(100, 0);
    auto point2 = MakePoint(0, 100);

    auto triangle = std::make_shared<Triangle>(&point0, &point1, &point2);

    for (int x = -200; x <= 300; x++) {
        for (int y = -200; y < 0; y++) {
            auto point = MakePoint(x, y);
            assert(!triangle->Contains(&point));
        }
        
        for (int y = 101; y <= 300; y++) {
            auto point = MakePoint(x, y);
            assert(!triangle->Contains(&point));
        }
    }

    for (int y = 0; y < 100; y++) {
        for (int x = -200; x < 0; x++) {
            auto point = MakePoint(x, y);
            assert(!triangle->Contains(&point));
        }

        for (int x = 101; x <= 300; x++) {
            auto point = MakePoint(x, y);
            assert(!triangle->Contains(&point));
        }
    }

    for (int x = 0; x <= 100; x++) {
        for (int y = 0; y <= 100 - x; y++) {
            auto point = MakePoint(x, y);
            assert(triangle->Contains(&point));
        }
        
        for (int y = 100 - x + 1; y <= 100; y++) {
            auto point = MakePoint(x, y);
            assert(!triangle->Contains(&point));
        }
    }
}