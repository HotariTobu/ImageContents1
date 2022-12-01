// Created by HotariTobu

#include <iostream>
#include <string>

#include "dat.h"
#include "main_helper.h"
#include "z_map.h"
#include "../include/calculator.h"
#include "../include/missing_value_remover.h"

#ifdef __4_NEIGHBOR
    #define FILENAME_SUFFIX_1 "_F_4N"
#elif __8_NEIGHBOR
    #define FILENAME_SUFFIX_1 "_F_8N"
#endif

#ifdef __MIN
    #define FILENAME_SUFFIX_2 "_MIN"
#elif __MAX
    #define FILENAME_SUFFIX_2 "_MAX"
#elif __MEAN
    #define FILENAME_SUFFIX_2 "_MEAN"
#elif __MEDIAN
    #define FILENAME_SUFFIX_2 "_MEDIAN"
#endif

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    filename_suffix += FILENAME_SUFFIX_1;
    filename_suffix += FILENAME_SUFFIX_2;
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    std::string destination_file_path = destination_base_path + filename_suffix + ".dat";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;
    

    auto&& [data, rectangle] = ReadDAT<double>(source_file_path);
    RemoveMissingValue(data);
    ZMap z_map(data, rectangle);
    
    Neighbor<double> neighbor(z_map.stride);
    while (!z_map.nan_point_indices.empty()) {
        auto ite = z_map.nan_point_indices.cbegin();

        while (ite != z_map.nan_point_indices.cend()) {
            int index = *ite;
            neighbor.head = &z_map.z_values[index];
            if (neighbor.IsAllNull()) {
                ++ite;
                continue;
            }

            ite = z_map.nan_point_indices.erase(ite);

            Point2d point = z_map.GetPoint(index);
            double z = Calculate(neighbor);

            auto pair = data.insert({point, z});
            z_map.z_values[index] = &pair.first->second;
        }
    }

    
    WriteDAT(destination_file_path, data);
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "FillerOption.txt", {
        {"source_directory_path", "intermediate_data_Splitter"},
        {"destination_directory_path", "intermediate_data_Filler"},
    }, init, process_file);
}