// Created by HotariTobu

#include "../include/face.h"

#include "neighbor.h"

double corner_threshold;

void Face::MarkInsidePoints() {
    Neighbor<ReducerAttribute*> neighbor(_z_map.stride);
    for (int i = 0; i < _z_map.size; ++i) {
        auto&& attribute = _z_map.z_values[i];
        if (attribute != nullptr) {
            neighbor.head = &attribute;

            bool is_removed = true;

            for (int i = 0; i < 4; ++i) {
                int offset_x = (-1 + i) % 2;
                int offset_y = (-2 + i) % 2;

                ReducerAttribute* dummy;
                is_removed &= neighbor.At(offset_x, offset_y, &dummy);
            }

            (*attribute)->is_removed = is_removed;

            if (is_removed) {
                _points_count--;
            }
        }
    }
}

void Face::MarkCornerPoints() {
    if (_points_count < 4) {
        return;
    }

    int start_index = _z_map.GetIndex(_z_map.width, 1);
    while (_z_map.z_values[start_index] == nullptr) {
        start_index += _z_map.stride;
    }

    std::list<int> indices = {start_index};

    static const std::pair<int, int> offsets[] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    auto get_next_index = [this](int index) {
        auto center = &_z_map.z_values[index];

        for (int i = 0; i < 8; ++i) {
            int offset_index = offsets[i].first + offsets[i].second * _z_map.stride;
            if (center + offset_index != nullptr) {
                return index + offset_index;
            }
        }
    };

    static const auto is_corcer = [](Point2d p0, Point2d p1)

    int prev_prev_index = start_index;
    int prev_index = get_next_index(prev_prev_index);
    int current_index = get_next_index(prev_index);

    while (current_index != start_index) {

    }
}