// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "dat.h"
#include "main_helper.h"
#include "vector3d.h"
#include "z_map.h"
#include "../include/face.h"
#include "../include/normal_vector_getter.h"
#include "../include/reducer_attribute.h"
#include "../include/searcher.h"

#ifdef __4_NEIGHBOR
    #define FILENAME_SUFFIX "_R_4N"
#elif __8_NEIGHBOR
    #define FILENAME_SUFFIX "_R_8N"
#endif

extern double searcher_threshold;

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    std::string searcher_threshold_str = option.at("searcher_threshold");
    searcher_threshold = std::stod(searcher_threshold_str);
    
    filename_suffix += FILENAME_SUFFIX;
    filename_suffix += "_SER" + searcher_threshold_str;
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    std::string destination_file_path = destination_base_path + filename_suffix + ".dat";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;


    auto&& [data, rectangle] = ReadDAT<ReducerAttribute>(source_file_path);
    ZMap z_map(data, rectangle);

    Neighbor<ReducerAttribute> neighbor_z_values(z_map.stride);
    for (int i = 0; i < z_map.size; ++i) {
        if (z_map.z_values[i] != nullptr) {
            neighbor_z_values.head = &z_map.z_values[i];
            Vector3d&& normal_vector = GetNormalVectorIn(neighbor_z_values);
            const_cast<ReducerAttribute*>(z_map.z_values[i])->normal_vector = normal_vector;
        }
    }


    auto indices_list = SearchPointGroups(z_map);

    for (auto&& indices : indices_list) {
        std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>> point_vector_list;
        for (int index : indices) {
            point_vector_list.push_back({
                {
                    z_map.GetPoint(index),
                    const_cast<double*>(&z_map.z_values[index]->z)
                },
                &z_map.z_values[index]->normal_vector
            });
        }

        Face face(point_vector_list);

        auto deleted_points = face.DeleteInsidePoints();
        for (auto&& deleted_point : deleted_points) {
            auto ite = data.find(deleted_point);
            data.erase(ite);
        }

        face.ProjectPoints();
    }

    WriteDAT(destination_file_path, data);
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "ReducerOption.txt", {
        {"source_directory_path", "intermediate_data_Judge"},
        {"destination_directory_path", "intermediate_data_Reducer"},
        {"searcher_threshold", "0.5"},
    }, init, process_file);
}