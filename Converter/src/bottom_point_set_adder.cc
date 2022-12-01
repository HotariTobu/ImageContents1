// Created by HotariTobu

#include "../include/bottom_point_set_adder.h"

#include <limits>

void AddBottomPointSet(const std::map<Point2d, Attribute>& data, Rectangle rectangle, std::list<std::pair<Point2d, double>>& additional_points, std::list<IndexSet>& additional_index_set_list, const std::list<std::pair<IndexSet, int>>& bottom_index_set_list) {
    double min_z = std::numeric_limits<double>().max();
    for (auto&& [_, attribute] : data) {
        if (min_z > attribute.z) {
            min_z = attribute.z;
        }
    }

    Point2d bottom_point_2d = {
        (rectangle.min_x + rectangle.max_x) / 2,
        (rectangle.min_y + rectangle.max_y) / 2
    };

    int bottom_index = data.size() + additional_points.size();
    additional_points.push_back({bottom_point_2d, min_z});

    for (auto [bottom_index_set, minus_index_index] : bottom_index_set_list) {
        bottom_index_set[minus_index_index] = bottom_index;
        additional_index_set_list.push_back(bottom_index_set);
    }
}