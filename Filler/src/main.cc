// Created by HotariTobu

#include <cctype>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

#include "csv_reader.h"
#include "csv_writer.h"
#include "option_reader_and_writer.h"
#include "../include/calculator.h"

namespace fs = std::filesystem;

std::string tolower(const std::string string) {
    std::string result;
    for (char c : string) {
        result.push_back(std::tolower(c));
    }
    return result;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    auto option = ReadAndWriteOption("FillerOption.txt", {
        {"source_directory_path", "intermediation_data_DATConverter"},
        {"destination_directory_path", "intermediation_data_Filler"},
    });

    std::string source_directory_path = option.at("source_directory_path");
    std::string destination_directory_path = option.at("destination_directory_path");

    if (!fs::exists(source_directory_path)) {
        std::cout << "Not exist: " << source_directory_path << std::endl;
        return 0;
    }

    fs::create_directories(destination_directory_path);

    for (const auto& file : fs::directory_iterator(source_directory_path)) {
        fs::path source_file_path = file.path();

        if (tolower(source_file_path.extension()) != ".csv") {
            continue;
        }

        fs::path basename = source_file_path.stem();
        fs::path destination_file_path = fs::path(destination_directory_path) / basename;

#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...

        destination_file_path += "__4_NEIGHBOR";

#elif __8_NEIGHBOR
// 8-neighbor code is hear...

        destination_file_path += "__8_NEIGHBOR";

#endif

#ifdef __MIN
    // Min code is hear...
    
        destination_file_path += "__MIN";

#elif __MAX
    // Max code is hear...
    
        destination_file_path += "__MAX";

#elif __MEAN
    // Mean code is hear...
    
        destination_file_path += "__MEAN";

#elif __MEDIAN
    // Median code is hear...
    
        destination_file_path += "__MEDIAN";

#endif

        destination_file_path += ".csv";

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
    }
}