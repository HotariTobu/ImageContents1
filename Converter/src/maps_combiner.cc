// Created by 

#include "../include/maps_combiner.h"

#include <cmath>

Map2d<double> CombineMaps(const std::vector<Map2d<double>>& maps) {
    Map2d<double> combine_maps = maps[0];

    for (int e = 1; e < maps.size(); ++e) {
        for (int y = 1; y <= maps[e].height; ++y) {
            for (int x = 1; x <= maps[e].width; ++x) {
                if (!std::isnan(maps[e].data[y][x])) {
                    combine_maps.data[y][x] = maps[e].data[y][x];
                }
            }
        }
    }
    return combine_maps;
}