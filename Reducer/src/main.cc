// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "csv_reader.h"
#include "csv_writer.h"
#include "main_helper.h"
#include "vector3d.h"
#include "../include/face.h"
#include "../include/normal_vector_getter.h"
#include "../include/searcher.h"

#ifdef __4_NEIGHBOR
    #define FILENAME_SUFFIX "_R_4N"
#elif __8_NEIGHBOR
    #define FILENAME_SUFFIX "_R_8N"
#endif

extern double searcher_threshold;

void init(std::map<std::string, std::string> option) {
    searcher_threshold = std::stod(option.at("searcher_threshold"));
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    HelpMain("ReducerOption.txt", {
        {"source_directory_path", "intermediation_data_Judge"},
        {"destination_directory_path", "intermediation_data_Reducer"},
        {"searcher_threshold", "0.5"},
    }, init, [nan](const std::string source_file_path, const std::string destination_base_path) {
        std::string destination_file_path = destination_base_path + FILENAME_SUFFIX + ".csv";
        std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;

        Map2d<double> map = ReadCSV(source_file_path);

        int width = map.width;
        int height = map.height;

        Map2d<std::pair<double, Vector3d>> normal_vector_map;
        normal_vector_map.width = width;
        normal_vector_map.height = height;
        normal_vector_map.data = std::vector<std::vector<std::pair<double, Vector3d>>>(height + 2, std::vector<std::pair<double, Vector3d>>(width + 2));

        for (int y = 1; y <= height; ++y) {
            for (int x = 1; x <= width; ++x) {
                Neighbor neighbor = {

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

                                       nan, map.data[y - 1][x],                    nan,
                    map.data[y    ][x - 1], map.data[y    ][x], map.data[y    ][x + 1],
                                       nan, map.data[y + 1][x],                    nan,

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

                    map.data[y - 1][x - 1], map.data[y - 1][x], map.data[y - 1][x + 1],
                    map.data[y    ][x - 1], map.data[y    ][x], map.data[y    ][x + 1],
                    map.data[y + 1][x - 1], map.data[y + 1][x], map.data[y + 1][x + 1],

#endif

                };

                double z = map.data[y][x];
                Vector3d normal_vector = GetNormalVectorIn(neighbor);

                normal_vector_map.data[y][x] = std::make_pair(z, normal_vector);
            }
        }

        int extended_width = width + 1;
        int extended_height = height + 1;

        for (int x = 1; x < extended_width; ++x) {
            normal_vector_map.data[0][x].first = nan;
            normal_vector_map.data[extended_height][x].first = nan;
        }
        
        for (auto row : normal_vector_map.data) {
            row[0].first = nan;
            row[extended_width].first = nan;
        }

        Map2d<double> result_map;
        result_map.x = map.x;
        result_map.y = map.y;
        result_map.width = width;
        result_map.height = height;
        result_map.data = std::vector<std::vector<double>>(height + 2, std::vector<double>(width + 2, nan));

        auto point_groups = SearchPointGroups(normal_vector_map);
        for (auto set : point_groups) {
            Face face(set);
            face.DeleteInsidePoints();
            face.ProjectPoints();

            for (Point3d point : face.points()) {
                result_map.data[point.y][point.x] = point.z;
            }
        }

        WriteCSV(destination_file_path, map);
    });
}