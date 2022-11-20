// Created by HotariTobu

#include "../include/triangle.h"

#include <array>
#include <cmath>
#include <map>
#include <vector>

std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>> MakeRoot(Point2d* p0, Point2d* p1, Point2d* p2) {
    std::map<double, Point2d*> points_with_angle;

    Point2d origin = (*p0 + *p1 + *p2) / 3;
    for (Point2d* point : {p0, p1, p2}) {
        Vector2d vector = *point - origin;
        double angle = std::atan2(vector.y, vector.x);

        points_with_angle.insert({angle, point});
    }

    std::vector<Point2d*> sorted_points;

    for (auto&& point_with_angle : points_with_angle) {
        sorted_points.push_back(point_with_angle.second);
    }

    auto root_triangle = std::make_shared<Triangle>(sorted_points[0], sorted_points[1], sorted_points[2]);
    auto dummy_triangle = std::make_shared<Triangle>(sorted_points[0], sorted_points[2], sorted_points[1]);

    root_triangle->neighbors[0] = dummy_triangle;
    root_triangle->neighbors[1] = dummy_triangle;
    root_triangle->neighbors[2] = dummy_triangle;
    dummy_triangle->neighbors[0] = root_triangle;
    dummy_triangle->neighbors[1] = root_triangle;
    dummy_triangle->neighbors[2] = root_triangle;

    return std::make_pair(root_triangle, dummy_triangle);
}