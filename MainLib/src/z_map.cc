// Created by HotariTobu

#include "../include/z_map.h"

ZMap::ZMap(const std::map<Point2d, double>& data, const Rectangle& rectangle) {
    this->rectangle = rectangle;

    this->width = rectangle.max_x - rectangle.min_x + 1;
    this->height = rectangle.max_y - rectangle.min_y + 1;
    
    this->stride = width + 2;

    this->z_values = std::make_unique<const double*[]>((width + 2) * (height + 2));

    auto data_end = data.end();
    for (int x = 1; x <= width; ++x) {
        for (int y = 1; y <= height; ++y) {
            auto ite = data.find({(double)x, (double)y});
            int index = x + y * stride;

            if (ite == data_end) {
                z_values[index] = nullptr;
                nan_point_indices.push_back(index);
            }
            else {
                z_values[index] = &ite->second;
            }
        }
    }

    int extended_width = width + 1;
    int extended_height = height + 1;
    int last_line = extended_height * stride;

    for (int x = 0; x <= extended_width; ++x) {
        z_values[x] = nullptr;
        z_values[last_line + x] = nullptr;
    }

    for (int i = 0; i <= last_line; i += width) {
        z_values[i] = nullptr;
        z_values[i + extended_width] = nullptr;
    }
}

Point2d ZMap::GetPoint(int index) const {
    int x = index % stride;
    int y = index / stride;

    return {
        rectangle.min_x + x,
        rectangle.min_y + y
    };
}