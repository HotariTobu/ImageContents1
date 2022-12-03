// Created by HotariTobu

#include "../include/dumper.h"

#include <filesystem>

#include "dat.h"

Dumper::Dumper(const std::string& file_path, std::map<Point2d, Attribute>* data, ZMap<Attribute>* z_map) {
    auto directory_path = std::filesystem::path(file_path);
    directory_path = directory_path.parent_path() / directory_path.stem();
    std::filesystem::create_directories(directory_path);
    
    this->_directory_path = directory_path.string();
    this->_data = data;
    this->_z_map = z_map;

    this->_max_ease_of_stay_value = 3;
    this->_count = 0;
}

void Dumper::Dump(const std::unique_ptr<double[]>& ease_of_stay_data) {
    for (int i = 0; i < _z_map->size; ++i) {
        if (_z_map->z_values[i] != nullptr) {
            double h = ease_of_stay_data[i] / _max_ease_of_stay_value;
            Color color(h, 1, 1);
            const_cast<Attribute*>(_z_map->z_values[i])->color = color;
        }
    }
    
    std::filesystem::path file_path(_directory_path);
    file_path /= std::to_string(++_count) + ".dat";

    WriteDAT(file_path.string(), *_data);
}