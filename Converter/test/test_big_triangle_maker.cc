// Created by HotariTobu

#include <cassert>
#include <tuple>

#include "random.h"
#include "../include/big_triangle_maker.h"
#include "../include/triangle.h"

bool CanPass() {
    constexpr int points_count = 20;

    static Random random(-100, 100);

    std::list<Point2d> raw_points;
    std::vector<IndexedPoint2d> points;
    for (int i = 0; i < points_count; i++) {
        Point2d raw_point;
        raw_point.x = random();
        raw_point.y = random();
        raw_points.push_back(raw_point);

        IndexedPoint2d point;
        point.index = i;
        point.point = &raw_points.back();
        points.push_back(point);
    }

    auto [p0, p1, p2] = MakeBigTriangle(points);
    IndexedPoint2d b0 {-1, &p0};
    IndexedPoint2d b1 {-2, &p1};
    IndexedPoint2d b2 {-3, &p2};
    Triangle triangle(&b0, &b1, &b2);

    for (auto&& point : points) {
        if (!triangle.Contains(&point)) {
            return false;
        }
    }

    return true;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        assert(CanPass());
    }
}