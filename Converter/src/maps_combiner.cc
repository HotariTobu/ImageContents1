// Created by D0000000000N

#include "../include/maps_combiner.h"

#include <cmath>

Map2d<std::pair<double, PointType>> CombineMaps(const std::list<std::pair<Map2d<double>, PointType>>& maps) {
    auto&& first_map = maps.front().first;

    int width = first_map.width;
    int height = first_map.height;

    Map2d<std::pair<double, PointType>> combine_maps;
    combine_maps.x = first_map.x;
    combine_maps.y = first_map.y;
    combine_maps.width = width;
    combine_maps.height = height;
    combine_maps.data = std::vector<std::vector<std::pair<double, PointType>>>(height + 2, std::vector<std::pair<double, PointType>>(width + 2, {0, PointType::NONE}));

    for (auto ite = maps.begin(); ite != maps.end(); ++ite) {
        for (int y = 1; y <= height; ++y) {
            for (int x = 1; x <= width; ++x) {
                if (!std::isnan(ite->first.data[y][x])) {
                    combine_maps.data[y][x] = {ite->first.data[y][x], ite->second};
                }
            }
        }
    }
    return combine_maps;
}