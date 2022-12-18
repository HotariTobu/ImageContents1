// Created by HotariTobu

#include <iostream>
#include <string>

#include "dat.h"
#include "main_helper.h"
#include "vector3d.h"
#include "z_map.h"
#include "../include/dumper.h"
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
extern int lowest_points_count;

static double normal_threshold;
static double projection_threshold;
static bool enable_dump;

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    std::string searcher_threshold_str = option.at("searcher_threshold");
    std::string normal_threshold_str = option.at("normal_threshold");
    std::string projection_threshold_str = option.at("projection_threshold");
    std::string lowest_points_count_str = option.at("lowest_points_count");
    std::string enable_dump_str = option.at("enable_dump");
    
    searcher_threshold = std::stod(searcher_threshold_str);
    normal_threshold = std::stod(normal_threshold_str);
    projection_threshold = std::stod(projection_threshold_str);
    lowest_points_count = std::stoi(lowest_points_count_str);
    enable_dump = enable_dump_str == "true";

    if (lowest_points_count <= 3) {
        throw std::runtime_error("`lowest_points_count` must be more than 3.");
    }
    
    filename_suffix += FILENAME_SUFFIX;
    filename_suffix += "_SER" + searcher_threshold_str;
    filename_suffix += "_NOR" + normal_threshold_str;
    filename_suffix += "_PRO" + projection_threshold_str;
    filename_suffix += "_LOW" + lowest_points_count_str;
}

void RemovePoints(std::map<Point2d, ReducerAttribute>& data) {
    auto ite = data.begin();
    while (ite != data.end()) {
        if (ite->second.is_removed) {
            ite = data.erase(ite);
        }
        else {
            ++ite;
        }
    }
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    std::string destination_file_path = destination_base_path + filename_suffix + ".dat";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;


    auto&& [data, rectangle] = ReadDAT<ReducerAttribute>(source_file_path);
    ZMap z_map(data, rectangle);

    std::unique_ptr<Dumper> dumper;
    if (enable_dump) {
        dumper = std::make_unique<Dumper>(destination_file_path, rectangle);
    }

    Neighbor<ReducerAttribute> neighbor_z_values(z_map.stride);
    for (int i = 0; i < z_map.size; ++i) {
        if (z_map.z_values[i] != nullptr) {
            neighbor_z_values.head = &z_map.z_values[i];
            Vector3d&& normal_vector = GetNormalVectorIn(neighbor_z_values);
            const_cast<ReducerAttribute*>(z_map.z_values[i])->normal_vector = normal_vector;

            if (normal_vector.z < normal_threshold) {
                z_map.z_values[i] = nullptr;
            }
        }
    }

    std::list<Point2d> normal_deleted_points;

    for (auto&& [point, attribute] : data) {
        if (attribute.normal_vector.z < normal_threshold) {
            normal_deleted_points.push_back(point);
        }
    }

    for (Point2d point : normal_deleted_points) {
        data.erase(point);
    }


    auto indices_list = SearchPointGroups(z_map);

    if (enable_dump) {
        const int offsets[] = {-z_map.stride, -1, 1, z_map.stride};

        for (auto&& indices : indices_list) {
            auto begin = indices.begin();
            auto end = indices.end();

            for (int index : indices) {
                Point2d point = z_map.GetPoint(index);

                bool is_removed = true;
                
                for (int offset : offsets) {
                    auto ite = std::find(begin, end, index + offset);
                    if (ite == end) {
                        is_removed = false;
                        break;
                    }
                }

                const_cast<ReducerAttribute*>(z_map.z_values[index])->is_removed = is_removed;
            }
        }
        dumper->Dump("groups.dat", data);
    }

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
            data.erase(deleted_point);
        }

        if (face.normal().z > projection_threshold) {
            face.ProjectPoints();
        }
    }

    WriteDAT(destination_file_path, data);
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "ReducerOption.txt", {
        {"source_directory_path", "intermediate_data_Judge"},
        {"destination_directory_path", "intermediate_data_Reducer"},
        {"searcher_threshold", "0.9"},
        {"normal_threshold", "0.7"},
        {"projection_threshold", "1"},
        {"lowest_points_count", "10"},
        {"enable_dump", "false"},
    }, init, process_file);
}