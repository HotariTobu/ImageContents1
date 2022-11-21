// Created by HotariTobu

#include "../include/dat.h"

#include <fstream>

template<typename T>
std::pair<std::map<Point2d, T>, Rectangle> ReadDAT(const std::string& path) {
    std::ifstream ifs(path);

    std::map<Point2d, T> data;

    double min_x = 0;
    double min_y = 0;
    double max_x = 0;
    double max_y = 0;

    while (ifs.good()) {
        double x, y;
        T t;

        ifs >> x >> y >> t;

        data.insert({{x, y}, t});

        if (min_x > x) {
            min_x = x;
        }
        else if (max_x < x) {
            max_x = x;
        }

        if (min_y > y) {
            min_y = y;
        }
        else if (max_y < y) {
            max_y = y;
        }
    }

    ifs.close();

    Rectangle rectangle(min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);

    return {data, rectangle};
}

template<typename T>
void WriteDAT(const std::string& path, const std::map<Point2d, T>& data) {
    std::ofstream ofs(path);

    for (auto [point, attribute] : data) {
        ofs << point.x << ' ' << point.y << ' ' << attribute << std::endl;
    }

    ofs.close();
}
