// Created by guinpen98

#include "../include/separator.h"

#include <cmath>

double separator_threshold;

void InitMap2d(const Map2d& origin, Map2d& init_to_map){
    init_to_map.width = origin.width;
    init_to_map.height = origin.height;
    init_to_map.data = std::vector<std::vector<double>>(init_to_map.height, std::vector<double>(init_to_map.width, std::nan("")));
}

std::pair<Map2d, Map2d> Separate(Map2d map, Map2d ease_of_stay) {
    Map2d ground_map;
    InitMap2d(map, ground_map);

    Map2d building_map;
    InitMap2d(map, ground_map);

    for(size_t y = 0; y < ease_of_stay.height; y++){
        for(size_t x = 0; x < ease_of_stay.width; x++){
            if(ease_of_stay.data[y][x] > separator_threshold){
                ground_map.data[y][x]=map.data[y][x];
            }
            else{
                building_map.data[y][x]=map.data[y][x];
            }
        }
    }

    return std::make_pair(ground_map, building_map);
}
