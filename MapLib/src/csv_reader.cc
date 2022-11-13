// Created by D0000000000N

#include "../include/csv_reader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

std::vector<std::string> split(std::string &input, char delimiter) {
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

Map2d<double> ReadCSV(std::string path) {
    Map2d<double> map;
    std::ifstream ifs(path);

    if (ifs) {
        std::string line;
        getline(ifs, line);
        std::vector<std::string> strvec = split(line, ',');
        map.x = std::stoi(strvec[0]);
        int x_max = std::stoi(strvec[1]);
        map.y = std::stoi(strvec[2]);
        int y_max = std::stoi(strvec[3]);
        map.width = x_max - map.x;
        map.height = y_max - map.y;
        while (getline(ifs, line)) {
            std::vector<double> datvec;
            std::vector<std::string> strvec = split(line, ',');
            for (auto &&s : strvec)
                if (s == "NaN") {
                    datvec.push_back(std::numeric_limits<double>::quiet_NaN());
                }
                else {
                    datvec.push_back(std::stod(s));
                }
            datvec.push_back(std::numeric_limits<double>::quiet_NaN());
            datvec.insert(datvec.begin(), std::numeric_limits<double>::quiet_NaN());
            map.data.insert(map.data.begin(), datvec);
        }
        std::vector<double> nanvec(strvec.size() + 2, std::numeric_limits<double>::quiet_NaN());
        map.data.insert(map.data.begin(), nanvec);
        map.data.push_back(nanvec);
    }

    return map;
}