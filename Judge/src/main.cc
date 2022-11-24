// Created by HotariTobu

#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "attribute.h"
#include "dat.h"
#include "main_helper.h"
#include "z_map.h"
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

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    simulator_threshold = std::stod(option.at("simulator_threshold"));
    separator_threshold = std::stod(option.at("separator_threshold"));
    trials_number = std::stoi(option.at("trials_number"));

    if (trials_number <= 0) {
        throw std::runtime_error("`trials_number` must be more than 0.");
    }

    filename_suffix = FILENAME_SUFFIX + std::to_string(simulator_threshold) + '|' + std::to_string(separator_threshold);
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    std::string destination_file_path = destination_base_path + filename_suffix + ".dat";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;


    auto&& [data, rectangle] = ReadDAT<Attribute>(source_file_path);
    ZMap z_map(data, rectangle);

    if (!z_map.nan_point_indices.empty()) {
        std::cout << "Warning: NaN points exist" << std::endl;
    }

    auto ease_of_stay_data_1 = std::make_unique<double[]>(z_map.size);
    auto ease_of_stay_data_2 = std::make_unique<double[]>(z_map.size);

    std::unique_ptr<double[]>* ease_of_stay_data_source = nullptr;
    std::unique_ptr<double[]>* ease_of_stay_data_destination = nullptr;

    Neighbor<Attribute> neighbor_z_values(z_map.stride);
    for (int i = 0; i < trials_number; ++i) {
        if (i % 2 == 0) {
            ease_of_stay_data_source = &ease_of_stay_data_1;
            ease_of_stay_data_destination = &ease_of_stay_data_2;
        }
        else {
            ease_of_stay_data_source = &ease_of_stay_data_2;
            ease_of_stay_data_destination = &ease_of_stay_data_1;
        }

        std::fill(ease_of_stay_data_destination->get(), ease_of_stay_data_destination->get() + z_map.size, 0);

        for (int x = 1; x <= z_map.width; ++x) {
            for (int y = 1; y <= z_map.height; ++y) {
                int index = z_map.GetIndex(x, y);
                double ease_of_stay_value = (*ease_of_stay_data_source)[index];
                neighbor_z_values.head = &z_map.z_values[index];

                auto ease_of_stay_values = Simulate(ease_of_stay_value, neighbor_z_values);

#ifdef __4_NEIGHBOR
// 4-neighbor _heightscode is hear...

                for (int i = 0; i < 4; ++i) {
                    int x = (-1 + i) % 2;
                    int y = (-2 + i) % 2;

                    int offset = z_map.GetIndex(x, y);

                    (*ease_of_stay_data_destination)[index + offset] += ease_of_stay_values[x + 1][y + 1];
                }

                (*ease_of_stay_data_destination)[index] += ease_of_stay_values[1][1];

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int offset = z_map.GetIndex(x, y);

                        (*ease_of_stay_data_destination)[index + offset] += ease_of_stay_values[x + 1][y + 1];
                    }
                }
                
#endif

            }
        }
    }

    for (int i = 0; i < z_map.size; ++i) {
        if (z_map.z_values[i] != nullptr) {
            double ease_of_stay_value = (*ease_of_stay_data_destination)[i];
            PointType&& point_type = ease_of_stay_value > separator_threshold ? PointType::GROUND : PointType::BUILDING;
            const_cast<Attribute*>(z_map.z_values[i])->type = point_type;
        }
    }
    
    WriteDAT(destination_file_path, data);
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