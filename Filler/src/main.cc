// Created by HotariTobu

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "csv_reader.h"
#include "csv_writer.h"
#include "main_helper.h"
#include "../include/calculator.h"

#ifdef __4_NEIGHBOR
    #define FILENAME_SUFFIX_1 "__4_NEIGHBOR"
#elif __8_NEIGHBOR
    #define FILENAME_SUFFIX_1 "__8_NEIGHBOR"
#endif

#ifdef __MIN
    #define FILENAME_SUFFIX_2 "__MIN"
#elif __MAX
    #define FILENAME_SUFFIX_2 "__MAX"
#elif __MEAN
    #define FILENAME_SUFFIX_2 "__MEAN"
#elif __MEDIAN
    #define FILENAME_SUFFIX_2 "__MEDIAN"
#endif

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    HelpMain("FillerOption.txt", {
        {"source_directory_path", "intermediation_data_DATConverter"},
        {"destination_directory_path", "intermediation_data_Filler"},
    }, [](auto option) {}, [](const std::string source_file_path, const std::string destination_base_path) {
        std::string destination_file_path = destination_base_path + FILENAME_SUFFIX_1 + FILENAME_SUFFIX_2 + ".csv";
        std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;

        Map2d<double> map = ReadCSV(source_file_path);

        for (int y = 1; y <= map.height; ++y) {
            for (int x = 1; x <= map.width; ++x) {
                if (!std::isnan(map.data[y][x])) {
                    continue;
                }

                Neighbor neighbor = {

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

                                       nan, map.data[y - 1][x],                    nan,
                    map.data[y    ][x - 1],                nan, map.data[y    ][x + 1],
                                       nan, map.data[y + 1][x],                    nan,

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

                    map.data[y - 1][x - 1], map.data[y - 1][x], map.data[y - 1][x + 1],
                    map.data[y    ][x - 1],                nan, map.data[y    ][x + 1],
                    map.data[y + 1][x - 1], map.data[y + 1][x], map.data[y + 1][x + 1],

#endif

                };

                map.data[y][x] = Calculate(neighbor);
            }
        }

        WriteCSV(destination_file_path, map);
    });
}