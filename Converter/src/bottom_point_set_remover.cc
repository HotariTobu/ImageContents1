// Created by HotariTobu

#include "../include/bottom_point_set_remover.h"

#include <cmath>
#include <map>
#include <vector>

#include "vector2d.h"

std::list<std::pair<Point2d, int>> RemoveBottomPointSet(std::list<IndexedPoint2dSet>& leaf_point_set_list, const Rectangle& rectangle) {
    std::map<std::pair<double, double>, std::pair<Point2d, int>> sorted_border_indexed_points;

    Point2d center_point_2d = {
        (rectangle.min_x + rectangle.max_x) / 2,
        (rectangle.min_y + rectangle.max_y) / 2
    };

    for (auto ite = leaf_point_set_list.cbegin(); ite != leaf_point_set_list.cend();) {
        auto&& point_set = *ite;

        std::vector<int> positive_point_indices;
        for (int i = 0; i < 3; ++i) {
            if (point_set[i].index >= 0) {
                positive_point_indices.push_back(i);
            }
        }
        int positive_points_count = positive_point_indices.size();
        
        if (positive_points_count == 3) {
            ++ite;
            continue;
        }

        if (positive_points_count == 2) {
            for (int point_index : positive_point_indices) {
                IndexedPoint2d point = point_set[point_index];
                Vector2d vector_2d = *point.point - center_point_2d;

                double angle = std::atan2(vector_2d.y, vector_2d.x);
                double length = vector_2d.Length();

                sorted_border_indexed_points.insert({{angle, length}, {*point.point, point.index}});
            }
        }

        ite = leaf_point_set_list.erase(ite);
    }

    std::list<std::pair<Point2d, int>> border_indexed_points;

    for (auto&& [_, indexed_point] : sorted_border_indexed_points) {
        border_indexed_points.push_back(indexed_point);
    }

    return border_indexed_points;
}