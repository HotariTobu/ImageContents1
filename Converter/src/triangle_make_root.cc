// Created by HotariTobu

#include "../include/triangle.h"

#include <algorithm>
#include <array>
#include <cmath>

std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>> MakeRoot(Point2d* p0, Point2d* p1, Point2d* p2) {
    std::array<Point2d*, 3> points = {p0, p1, p2};

    Point2d origin;
    for (int i = 0; i < 3; i++) {
        origin += *points[i];
    }
    origin /= 3;
    
    std::array<int, 3> indices;
    std::array<double, 3> angles;

    for (int i = 0; i < 3; i++) {
        indices[i] = i;

        Point2d point = *points[i];
        Vector2d vector = point - origin;
        angles[i] = std::atan2(point.y, point.x);
    }

    std::sort(indices.begin(), indices.end(), [angles](int i1, int i2) { return angles[i1] < angles[i2]; });

    auto root_triangle = std::make_shared<Triangle>(points[indices[0]], points[indices[1]], points[indices[2]]);
    auto dummy_triangle = std::make_shared<Triangle>(points[indices[0]], points[indices[2]], points[indices[1]]);

    root_triangle->neighbors[0] = dummy_triangle;
    root_triangle->neighbors[1] = dummy_triangle;
    root_triangle->neighbors[2] = dummy_triangle;
    dummy_triangle->neighbors[0] = root_triangle;
    dummy_triangle->neighbors[1] = root_triangle;
    dummy_triangle->neighbors[2] = root_triangle;

    return std::make_pair(root_triangle, dummy_triangle);
}