// Created by HotariTobu

#include <iostream>
#include <set>
#include <string>
#include <cmath>

#include "csv_reader.h"
#include "main_helper.h"
#include "../include/big_triangle_maker.h"
#include "../include/ground_points_adder.h"
#include "../include/maps_combiner.h"
#include "../include/randomizer.h"
#include "../include/triangle.h"
#include "../include/wrl_writer.h"

/*
Trim a string with a suffix.
[params]
- string: string being trimmed
- suffix: string to be removed
[return]
Return the trimmed string if the end matches the suffix other else the original string.
*/
std::string TrimEnd(std::string string, std::string suffix) {
    int string_length = string.size();
    int suffix_length = suffix.size();
    int difference = string_length - suffix_length;

    if (difference < 0) {
        return string;
    }

    for (int i = 0; i < suffix_length; ++i) {
        if (string[difference + i] != suffix[i]) {
            return string;
        }
    }

    return string.substr(0, difference);
}

extern double ground_point_threshold;

std::string threshold_suffix;
std::set<std::string> source_base_paths;

void init(std::map<std::string, std::string> option) {
    ground_point_threshold = std::stod(option.at("ground_point_threshold"));
    threshold_suffix = std::to_string(ground_point_threshold);
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    std::string source_base_path = TrimEnd(source_file_path, "_ground.csv");
    source_base_path = TrimEnd(source_base_path, "_building.csv");

    auto source_base_path_iterator = source_base_paths.find(source_base_path);
    if (source_base_path_iterator == source_base_paths.end()) {
        source_base_paths.insert(source_base_path);
        return;
    }

    source_base_paths.erase(source_base_path_iterator);


    std::string source_file_path_ground = source_base_path + "_ground.csv";
    std::string source_file_path_building = source_base_path + "_building.csv";

    std::string destination_file_path = destination_base_path + std::to_string(ground_point_threshold) + threshold_suffix + ".wrl";
    std::cout << "Converting: " << source_file_path_ground << ", " << source_file_path_building << " > " << destination_file_path << std::endl;


    auto map_ground = ReadCSV(source_file_path_ground);
    auto map_building = ReadCSV(source_file_path_building);

    auto map = CombineMaps({
        {map_ground, PointType::GROUND},
        {map_building, PointType::BUILDING},
    });

    map_ground.data.clear();
    map_building.data.clear();

    int width = map.width;
    int height = map.height;

    std::vector<Point2d> points;
    points.reserve(map.width * map.height / 2);

    for (int y = 1; y <= height; ++y) {
        for (int x = 1; x <= width; ++x) {
            double z = map.data[y][x].first;
            if (std::isnan(z)) {
                continue;
            }

            Point2d point;
            point.x = x;
            point.y = y;
            points.push_back(point);
        }
    }

    if (points.empty()) {
        return;
    }


    auto [p0, p1, p2] = MakeBigTriangle(points);
    auto [root_triangle, dummy_triangle] = MakeRoot(&p0, &p1, &p2);

    Randomize(points);

    std::vector<double> z_values;
    z_values.reserve(points.size());

    for (auto&& point : points) {
        root_triangle->Divide(&point);

        int x = point.x;
        int y = point.y;
        z_values.push_back(map.data[y][x].first);
    }

    auto leaves = root_triangle->GetAllLeaves();
    std::vector<IndexSet> triangle_indices;
    triangle_indices.reserve(leaves.size());

    Point2d* points_head = points.data();
    for (auto leaf : leaves) {
        auto accessible_leaf = leaf.lock();
        IndexSet index_set = {
            (int)(accessible_leaf->points[0] - points_head),
            (int)(accessible_leaf->points[1] - points_head),
            (int)(accessible_leaf->points[2] - points_head),
        };

        triangle_indices.push_back(index_set);
    }

    AddGroundPoints(points, z_values, triangle_indices);

    WriteWRL(destination_file_path, points, z_values, triangle_indices, map);
}

/*
Read 2 .csv file.
*/
int main() {
    HelpMain("ConverterOption.txt", {
        {"source_directory_path", "intermediate_data_Reducer"},
        {"destination_directory_path", "destination_data"},
        {"ground_point_threshold", "0.5"},
    }, init, process_file);
}