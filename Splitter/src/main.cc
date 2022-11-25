// Created by HotariTobu

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "dat.h"
#include "main_helper.h"
#include "z_map.h"

int chunk_length;

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    chunk_length = std::stoi(option.at("chunk_length"));
    filename_suffix = "_CL_" + std::to_string(chunk_length);
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    auto&& [data, rectangle] = ReadDAT<double>(source_file_path);
    ZMap z_map(data, rectangle);

    int columns_count = z_map.width / chunk_length + 1;
    int rows_count = z_map.height / chunk_length + 1;

    auto chunks = std::vector<std::vector<std::map<Point2d, double>>>(columns_count, std::vector<std::map<Point2d, double>>(rows_count));

    for (int x = 1; x <= z_map.width; ++x) {
        for (int y = 1; y <= z_map.height; ++y) {
            int column = x / chunk_length;
            int row = y / chunk_length;

            int index = z_map.GetIndex(x, y);

            auto z_pointer = z_map.z_values[index];
            if (z_pointer == nullptr) {
                continue;
            }

            Point2d point = z_map.GetPoint(index);
            double z = *z_pointer;

            chunks[column][row].insert({point, z});
        }
    }
    
    for (int column = 0; column < columns_count; ++column) {
        for (int row = 0; row < rows_count; ++row) {
            std::string chunk_suffix = '_' + std::to_string(column) + '-' + std::to_string(row);
            std::string destination_file_path = destination_base_path + filename_suffix + chunk_suffix + ".dat";
            std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;

            WriteDAT(destination_file_path, chunks[column][row]);
        }
    }
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "SplitterOption.txt", {
        {"source_directory_path", "source_data"},
        {"destination_directory_path", "intermediate_data_Splitter"},
        {"chunk_length", "100"},
    }, init, process_file);
}