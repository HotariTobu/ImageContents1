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
    std::string simulator_threshold_str = option.at("simulator_threshold");
    std::string separator_threshold_str = option.at("separator_threshold");
    std::string trials_number_str = option.at("trials_number");
    simulator_threshold = std::stod(simulator_threshold_str);
    separator_threshold = std::stod(separator_threshold_str);
    trials_number = std::stoi(trials_number_str);

    if (trials_number <= 0) {
        throw std::runtime_error("`trials_number` must be more than 0.");
    }

    filename_suffix += FILENAME_SUFFIX;
    filename_suffix += "_SIM" + simulator_threshold_str;
    filename_suffix += "_SEP" + separator_threshold_str;
    filename_suffix += "_TRY" + trials_number_str;
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

    std::fill(ease_of_stay_data_1.get(), ease_of_stay_data_1.get() + z_map.size, 1);

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
                    int offset_x = (-1 + i) % 2;
                    int offset_y = (-2 + i) % 2;

                    int offset = z_map.GetIndex(offset_x, offset_y);

                    (*ease_of_stay_data_destination)[index + offset] += ease_of_stay_values[offset_x + 1][offset_y + 1];
                }

                (*ease_of_stay_data_destination)[index] += ease_of_stay_values[1][1];

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

                for (int offset_x = -1; offset_x <= 1; ++offset_x) {
                    for (int offset_y = -1; offset_y <= 1; ++offset_y) {
                        int offset = z_map.GetIndex(offset_x, offset_y);

                        (*ease_of_stay_data_destination)[index + offset] += ease_of_stay_values[offset_x + 1][offset_y + 1];
                    }
                }
                
#endif

            }
        }
    }

    for (int i = 0; i < z_map.size; ++i) {
        if (z_map.z_values[i] != nullptr) {
            const Color ground_color(0.33, 1, 1);
            const Color building_color(0, 1, 1);
            
            double ease_of_stay_value = (*ease_of_stay_data_destination)[i];
            Color color = ease_of_stay_value > separator_threshold ? ground_color : building_color;
            const_cast<Attribute*>(z_map.z_values[i])->color = color;
        }
    }
    
    WriteDAT(destination_file_path, data);
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "JudgeOption.txt", {
        {"source_directory_path", "intermediate_data_Filler"},
        {"destination_directory_path", "intermediate_data_Judge"},
        {"simulator_threshold", "2"},
        {"separator_threshold", "2"},
        {"trials_number", "10"},
    }, init, process_file);
}