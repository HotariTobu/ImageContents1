// Created by HotariTobu

#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "point3d.h"
#include "../include/wrl_writer.h"

std::pair<std::list<IndexedPoint2dSet>, std::vector<IndexedPoint2d>> GetPointSetList(int points_count, const std::list<IndexSet>& index_set_list) {
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
            point_set[i] = &points[index_set[i]];
        }
        
    }
    
    return {point_set_list, points};
}

bool CanPass(const char* answer, const std::map<Point2d, Attribute>& data, const std::list<IndexSet>& index_set_list, const std::list<std::pair<Point2d, double>>& additional_points = {}, const std::list<IndexSet>& additional_index_set_list = {}) {
    const char* filename = "test.wrl";

    auto [point_set_list, points] = GetPointSetList(data.size(), index_set_list);

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
    geometry IndexedFaceSet {
        colorPerVertex TRUE
        color Color {
            color [
0 1 0,
1 0 0,
0 1 0,
1 1 1,
0 1 0,
            ]
        }
        coord Coordinate {
            point [
0 3 -1,
1 6 -0,
2 9 -2,
1 7 -2,
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
            {{0, 1}, {3, PointType::GROUND}},
            {{1, 0}, {6, PointType::BUILDING}},
            {{2, 2}, {9, PointType::GROUND}},
            {{1, 2}, {7, PointType::NONE}},
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