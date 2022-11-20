// Created by HotariTobu

#include "../include/dat.h"

#include <fstream>

template<typename T>
std::map<Point2d, T> ReadDAT(const std::string& path) {
    std::ifstream ifs(path);

    std::map<Point2d, T> data;

    while (ifs.good()) {
        double x, y;
        T t;

        ifs >> x >> y >> t;

        data.insert({{x, y}, t});
    }

    ifs.close();

    return data;
}

template<typename T>
void WriteDAT(const std::string& path, const std::map<Point2d, T>& data) {
    std::ofstream ofs(path);

    for (auto [point, attribute] : data) {
        ofs << point.x << ' ' << point.y << ' ' << attribute << std::endl;
    }

    ofs.close();
}
