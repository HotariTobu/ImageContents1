// Created by HotariTobu

#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include "point3d.h"
#include "../include/wrl_writer.h"

bool CanPass(const char* answer, const std::map<Point2d, Attribute>& data, const std::list<IndexSet>& index_set_list, const std::list<std::pair<Point2d, double>>& additional_points = {}, const std::list<IndexSet>& additional_index_set_list = {}) {
    const char* filename = "test.wrl";


    int points_count = data.size();

    std::vector<IndexedPoint2d> points;
    points.reserve(points_count);

    for (int i = 0; i < points_count; i++) {
        IndexedPoint2d point;
        point.index = i;
        points.push_back(point);
    }
    
    std::list<IndexedPoint2dSet> point_set_list;

    for (auto &&index_set : index_set_list) {
        IndexedPoint2dSet point_set;
        for (int i = 0; i < 3; i++) {
            point_set[i] = points[index_set[i]];
        }
        point_set_list.push_back(point_set);
    }
    

    WriteWRL(filename, data, point_set_list, additional_points, additional_index_set_list);

    std::ifstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();

    std::string result = buffer.str();

    std::filesystem::remove(filename);

    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    assert(CanPass(
        R"(#VRML V2.0 utf8

Shape {
    appearance Appearance {
        material Material {}
    }
    geometry IndexedFaceSet {
        color Color {
            color [
0.02 1 0,
1 0 0,
0 0 0,
0.02 1 0,
0.02 1 0,
            ]
        }
        coord Coordinate {
            point [
0 3 -1,
1 6 -0,
1 7 -2,
2 9 -2,
2 0 -2,
            ]
        }
        coordIndex [
0, 1, 2, -1
0, 1, 3, -1
2, 1, 0, -1
        ]
    }
})",
        {
            {{0, 1}, {3, Color(0.33, 1, 1)}},
            {{1, 0}, {6, Color(0, 1, 1)}},
            {{1, 2}, {7, Color()}},
            {{2, 2}, {9, Color(0.33, 1, 1)}},
        },
        {
            {0, 1, 2},
            {0, 1, 3},
        },
        {
            {{2, 2}, 0},
        },
        {
            {2, 1, 0},
        }
    ));
}