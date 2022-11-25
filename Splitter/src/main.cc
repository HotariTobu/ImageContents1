// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "dat.h"
#include "main_helper.h"
#include "z_map.h"

double chunk_length;

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    chunk_length = std::stod(option.at("chunk_length"));
    filename_suffix = "_CL_" + std::to_string(chunk_length);
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    auto&& [data, rectangle] = ReadDAT<double>(source_file_path);
    ZMap z_map(data, rectangle);

    int columns_count = std::ceil(z_map.width / chunk_length);
    int rows_count = std::ceil(z_map.height / chunk_length);

    auto chunks = std::vector<std::vector<std::map<Point2d, double>>>(columns_count, std::vector<std::map<Point2d, double>>(rows_count));

    for (int x = 1; x <= z_map.width; ++x) {
        for (int y = 1; y <= z_map.width; ++y) {
            int column = x / chunk_length;
            int row = y / chunk_length;

            int index = z_map.GetIndex(x, y);

            Point2d point = z_map.GetPoint(index);
            double z = *z_map.z_values[index];

            chunks[column][row].insert({point, z});
        }
    }
    
    for (int column = 0; column < columns_count; ++column) {
        for (int row = 0; row < rows_count; ++row) {
            std::string chunk_suffix = std::to_string(column) + '-' + std::to_string(row);
            std::string destination_file_path = destination_base_path + filename_suffix + chunk_suffix + ".dat";
            std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;

            WriteDAT(destination_file_path, chunks[column][row]);
        }
    }
}

int main() {
    HelpMain("FillerOption.txt", {
        {"source_directory_path", "source_data"},
        {"destination_directory_path", "intermediate_data_Splitter"},
    }, init, process_file);
}