// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "csv_reader.h"
#include "csv_writer.h"
#include "main_helper.h"
#include "../include/simulator.h"
#include "../include/separator.h"

#ifdef __4_NEIGHBOR
    #define FILENAME_SUFFIX "_J_4N"
#elif __8_NEIGHBOR
    #define FILENAME_SUFFIX "_J_8N"
#endif

extern double simulator_threshold;
extern double separator_threshold;

static int trials_number;

constexpr double nan = std::numeric_limits<double>::quiet_NaN();

std::string threshold_suffix;

void init(std::map<std::string, std::string> option) {
    simulator_threshold = std::stod(option.at("simulator_threshold"));
    separator_threshold = std::stod(option.at("separator_threshold"));
    trials_number = std::stoi(option.at("trials_number"));

    if (trials_number <= 0) {
        throw std::runtime_error("`trials_number` must be more than 0.");
    }

    threshold_suffix = std::to_string(simulator_threshold) + '|' + std::to_string(separator_threshold);
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    std::string destination_file_path_ground = destination_base_path + FILENAME_SUFFIX + threshold_suffix + "_ground.csv";
    std::string destination_file_path_building = destination_base_path + FILENAME_SUFFIX + threshold_suffix + "_building.csv";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path_ground << ", " << destination_file_path_building << std::endl;

    Map2d<double> map = ReadCSV(source_file_path);

    int width = map.width;
    int height = map.height;

    std::vector<std::vector<double>> ease_of_stay_data_1;
    std::vector<std::vector<double>> ease_of_stay_data_2;

    ease_of_stay_data_1 = std::vector<std::vector<double>>(height + 2, std::vector<double>(width + 2, 1));

    std::vector<std::vector<double>>* ease_of_stay_data_source = nullptr;
    std::vector<std::vector<double>>* ease_of_stay_data_destination = nullptr;

    for (int i = 0; i < trials_number; ++i){
        if (i % 2 == 0) {
            ease_of_stay_data_source = &ease_of_stay_data_1;
            ease_of_stay_data_destination = &ease_of_stay_data_2;
        }
        else {
            ease_of_stay_data_source = &ease_of_stay_data_2;
            ease_of_stay_data_destination = &ease_of_stay_data_1;
        }

        *ease_of_stay_data_destination = std::vector<std::vector<double>>(height + 2, std::vector<double>(width + 2, 0));

        for (int y = 1; y <= height; ++y) {
            for (int x = 1; x <= width; ++x) {
                double ease_of_stay_value = (*ease_of_stay_data_source)[y][x];

                Neighbor neighbor_heights = {

#ifdef __4_NEIGHBOR
// 4-neighbor _heightscode is hear...

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
        
                Neighbor neighbor_ease_of_stay_values = Simulate(ease_of_stay_value, neighbor_heights);

#ifdef __4_NEIGHBOR
// 4-neighbor _heightscode is hear...

                (*ease_of_stay_data_destination)[y - 1][x] += neighbor_ease_of_stay_values.data[0][1];
                (*ease_of_stay_data_destination)[y][x - 1] += neighbor_ease_of_stay_values.data[1][0];
                (*ease_of_stay_data_destination)[y][x    ] += neighbor_ease_of_stay_values.data[1][1];
                (*ease_of_stay_data_destination)[y][x + 1] += neighbor_ease_of_stay_values.data[1][2];
                (*ease_of_stay_data_destination)[y + 1][x] += neighbor_ease_of_stay_values.data[2][1];

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

                (*ease_of_stay_data_destination)[y - 1][x - 1] += neighbor_ease_of_stay_values.data[0][0];
                (*ease_of_stay_data_destination)[y - 1][x    ] += neighbor_ease_of_stay_values.data[0][1];
                (*ease_of_stay_data_destination)[y - 1][x + 1] += neighbor_ease_of_stay_values.data[0][2];
                (*ease_of_stay_data_destination)[y    ][x - 1] += neighbor_ease_of_stay_values.data[1][0];
                (*ease_of_stay_data_destination)[y    ][x    ] += neighbor_ease_of_stay_values.data[1][1];
                (*ease_of_stay_data_destination)[y    ][x + 1] += neighbor_ease_of_stay_values.data[1][2];
                (*ease_of_stay_data_destination)[y + 1][x - 1] += neighbor_ease_of_stay_values.data[2][0];
                (*ease_of_stay_data_destination)[y + 1][x    ] += neighbor_ease_of_stay_values.data[2][1];
                (*ease_of_stay_data_destination)[y + 1][x + 1] += neighbor_ease_of_stay_values.data[2][2];

#endif

            }
        }
    }

    Map2d<std::pair<double, double>> ease_of_stay_map;
    ease_of_stay_map.x = map.x;
    ease_of_stay_map.y = map.y;
    ease_of_stay_map.width = width;
    ease_of_stay_map.height = height;
    ease_of_stay_map.data = std::vector<std::vector<std::pair<double, double>>>(height + 2, std::vector<std::pair<double, double>>(width + 2));

    for (int y = 1; y <= height; ++y) {
        for (int x = 1; x <= width; ++x) {
            ease_of_stay_map.data[y][x] = std::make_pair(map.data[y][x], (*ease_of_stay_data_destination)[y][x]);
        }
    }

    auto [map_ground, map_building] = Separate(ease_of_stay_map);

    WriteCSV(destination_file_path_ground, map_ground);
    WriteCSV(destination_file_path_building, map_building);
}

int main() {
    HelpMain("JudgeOption.txt", {
        {"source_directory_path", "intermediate_data_Filler"},
        {"destination_directory_path", "intermediate_data_Judge"},
        {"simulator_threshold", "2"},
        {"separator_threshold", "2"},
        {"trials_number", "10"},
    }, init, process_file);
}