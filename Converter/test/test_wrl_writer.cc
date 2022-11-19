// Created by HotariTobu

#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "point3d.h"
#include "../include/wrl_writer.h"

bool CanPass(std::vector<Point3d> points, std::vector<IndexSet> indices, Map2d<PointType> point_types, const char* answer) {
    const char* filename = "test.wrl";

    std::vector<Point2d> points_2d(points.size());
    std::vector<double> z_values(points.size());
    for (int i = 0; i < points.size(); i++) {
        points_2d[i] = {
            points[i].x,
            points[i].y
        };
        z_values[i] = points[i].z;
    }

    Map2d<std::pair<double, PointType>> map;
    double width = point_types.width;
    double height = point_types.height;
    map.data = std::vector<std::vector<std::pair<double, PointType>>>(height + 2, std::vector<std::pair<double, PointType>>(width + 2, {0, PointType::NONE}));
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            map.data[y][x].second = point_types.data[y][x];
        }
    }
    

    WriteWRL(filename, points_2d, z_values, indices, map);

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

    assert(
        CanPass(
            {
                {0, 1, 3},
                {1, 0, 6},
                {2, 2, 9},
                {1, 2, 7},
            },
            {
                {0, 1, 2},
                {0, 1, 3},
            },
            {
                -2, 7, 3, 3,
                {
                    {PointType::NONE,   PointType::NONE,     PointType::NONE,   PointType::NONE, PointType::NONE},
                    {PointType::NONE,   PointType::NONE, PointType::BUILDING,   PointType::NONE, PointType::NONE},
                    {PointType::NONE, PointType::GROUND,     PointType::NONE,   PointType::NONE, PointType::NONE},
                    {PointType::NONE,   PointType::NONE,     PointType::NONE, PointType::GROUND, PointType::NONE},
                    {PointType::NONE,   PointType::NONE,     PointType::NONE,   PointType::NONE, PointType::NONE},
                }
            },
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
            ]
        }
        coord Coordinate {
            point [
0 3 -1,
1 6 -0,
2 9 -2,
1 7 -2,
            ]
        }
        coordIndex [
0, 1, 2, -1
0, 1, 3, -1
        ]
    }
})"
        )
    );
}