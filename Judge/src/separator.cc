// Created by guinpen98

#include "../include/separator.h"

#include <cmath>

double separator_threshold;

void InitMap2d(const Map2d<std::pair<double, double>>& origin, Map2d<double>& init_to_map){
    init_to_map.width = origin.width;
    init_to_map.height = origin.height;
    init_to_map.data = std::vector<std::vector<double>>(init_to_map.height + 2, std::vector<double>(init_to_map.width + 2, std::nan("")));
}

std::pair<Map2d<double>, Map2d<double>> Separate(const Map2d<std::pair<double, double>>& map) {
    Map2d<double> ground_map;
    InitMap2d(map, ground_map);

    Map2d<double> building_map;
    InitMap2d(map, building_map);

    for(int y = 0; y < map.height; y++){
        for(int x = 0; x < map.width; x++){
            if(map.data[y][x].second > separator_threshold){
                ground_map.data[y][x] = map.data[y][x].first;
            }
            else{
                building_map.data[y][x] = map.data[y][x].first;
            }
        }
    }

    return std::make_pair(ground_map, building_map);
}
