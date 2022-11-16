// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

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

void init(std::map<std::string, std::string> option) {
}

/*
Read 2 .csv file.
*/
int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    std::vector<std::string> source_base_paths;

    HelpMain("ConverterOption.txt", {
        {"source_directory_path", "intermediation_data_Reducer"},
        {"destination_directory_path", "destination_data"},
    }, init, [nan, &source_base_paths](const std::string source_file_path, const std::string destination_base_path) {
        std::string source_base_path = TrimEnd(source_file_path, "_ground.csv");
        source_base_path = TrimEnd(source_file_path, "_building.csv");

        auto source_base_paths_end = source_base_paths.end();
        auto source_base_path_iterator = std::find(source_base_paths.begin(), source_base_paths_end, source_base_path);
        if (source_base_path_iterator == source_base_paths_end) {
            source_base_paths.push_back(source_base_path);
            return;
        }

        source_base_paths.erase(source_base_path_iterator);

        std::string source_file_path_ground = source_base_path + "_ground.csv";
        std::string source_file_path_building = source_base_path + "_building.csv";

        std::string destination_file_path = destination_base_path + ".wrl";
        std::cout << "Converting: " << source_file_path_ground << ", " << source_file_path_building << " > " << destination_file_path << std::endl;

        Map2d<double> map_ground = ReadCSV(source_file_path_ground);
        Map2d<double> map_building = ReadCSV(source_file_path_building);

        Map2d<double> map = CombineMaps({map_ground, map_building});

        int width = map.width;
        int height = map.height;

        PointSet points;
        points.reserve(map.width * map.height / 2);

        Map2d<PointType> point_types;
        point_types.data = std::vector<std::vector<PointType>>(height + 2, std::vector<PointType>(width + 2, PointType::NONE));

        for (int y = 1; y <= height; ++y) {
            for (int x = 1; x <= width; ++x) {
                double z = map.data[y][x];
                if (std::isnan(z)) {
                    continue;
                }

                Point3d point{(double)x, (double)y, z};
                points.push_back(point);

                if (!std::isnan(map_ground.data[y][x])) {
                    point_types.data[y][x] = PointType::GROUND;
                }
                else if (!std::isnan(map_building.data[y][x])) {
                    point_types.data[y][x] = PointType::BUILDING;
                }
            }
        }

        if (points.size() == 0) {
            return;
        }

        auto [p0, p1, p2] = MakeBigTriangle(points);
        Triangle root_triangle(&p0, &p1, &p2);

        Randomize(points);

        for (auto point : points) {
            root_triangle.Divide(&point);
        }

        auto leaves = root_triangle.GetAllLeaves();
        std::vector<IndexSet> triangle_indices;
        triangle_indices.reserve(leaves.size());

        Point3d* points_head = points.data();
        for (auto leaf : leaves) {
            IndexSet index_set = {
                (int)(leaf->points[0] - points_head),
                (int)(leaf->points[1] - points_head),
                (int)(leaf->points[2] - points_head),
            };

            triangle_indices.push_back(index_set);
        }

        AddGroundPoints(points, triangle_indices);

        WriteWRL(destination_file_path, points, triangle_indices, point_types);
    });
}