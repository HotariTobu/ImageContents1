// Created by HotariTobu

#include "../include/dumper.h"

#include <filesystem>

#include "dat.h"

Dumper::Dumper(const std::string& file_path, std::map<Point2d, ReducerAttribute>* data, ZMap<ReducerAttribute>* z_map) {
    auto directory_path = std::filesystem::path(file_path);
    directory_path = directory_path.parent_path() / directory_path.stem();
    std::filesystem::create_directories(directory_path);
    
    this->_directory_path = directory_path.string();
    this->_data = data;
    this->_z_map = z_map;
}

void Dumper::Dump(std::list<std::list<int>> indices_list) {
    int groups_count = indices_list.size();

    int i = 0;
    for (auto&& indices : indices_list) {
        constexpr int color_range = 256 * 256 * 256;
        int color_value = ++i * color_range / groups_count;

        int r = color_value % 256;
        color_value /= 256;
        int g = color_value % 256;
        color_value /= 256;
        int b = color_value % 256;

        Color color;
        color.r = r / 256.0;
        color.g = g / 256.0;
        color.b = b / 256.0;

        for (int index : indices) {
            const_cast<ReducerAttribute*>(_z_map->z_values[index])->color = color;
        }
    }
    
    std::filesystem::path file_path(_directory_path);
    file_path /= "groups.dat";

    WriteDAT(file_path.string(), *_data);
}