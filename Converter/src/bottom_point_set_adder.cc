// Created by HotariTobu

#include "../include/bottom_point_set_adder.h"

#include <limits>

void AddBottomPointSet(const std::map<Point2d, Attribute>& data, std::list<std::pair<Point2d, double>>& additional_points, std::list<IndexSet>& additional_index_set_list, std::list<std::pair<Point2d, int>>& border_indexed_points) {
    double min_z = std::numeric_limits<double>().max();
    for (auto&& [_, attribute] : data) {
        if (min_z > attribute.z) {
            min_z = attribute.z;
        }
    }
    min_z -= 0.1;

    auto [first_border_point, first_border_index] = border_indexed_points.front();
    border_indexed_points.pop_front();

    int first_bottom_index = data.size() + additional_points.size();
    int bottom_index = first_bottom_index;
    additional_points.push_back({first_border_point, min_z});

    int last_border_index = first_border_index;
    for (auto&& [border_point, border_index] : border_indexed_points) {
        ++bottom_index;
        additional_points.push_back({border_point, min_z});

        IndexSet upper_index_set = {
            last_border_index,
            bottom_index,
            border_index
        };

        IndexSet lower_index_set = {
            last_border_index,
            bottom_index - 1,
            bottom_index
        };

        IndexSet bottom_index_set = {
            first_bottom_index,
            bottom_index,
            bottom_index - 1,
        };

        last_border_index = border_index;

        additional_index_set_list.push_back(upper_index_set);
        additional_index_set_list.push_back(lower_index_set);
        additional_index_set_list.push_back(bottom_index_set);
    }
    
    IndexSet first_upper_index_set = {
        last_border_index,
        first_bottom_index,
        first_border_index
    };

    IndexSet first_lower_index_set = {
        last_border_index,
        bottom_index,
        first_bottom_index
    };

    additional_index_set_list.push_back(first_upper_index_set);
    additional_index_set_list.push_back(first_lower_index_set);
}
