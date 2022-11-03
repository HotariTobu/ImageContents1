// Created by 

#include <cassert>

#include "../include/wrl_writer.h"

bool CanPass(PointSet points, std::vector<IndexSet> indices, Map2d<PointType> point_types, const char* answer) {
    constexpr char* filename = "test.wrl";

    WriteWRL(filename, points, indices, point_types);

    std::ifstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();

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
            },
            {
                {0, 1, 2},
            },
            {
                0, 0, 3, 3,
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
                0 255 0,
                255 0 0,
                0 255 0,
            ]
        }
        coord Coordinate {
            point [
                0 1 3,
                1 0 6,
                2 2 9,
            ]
        }
        coordIndex [
            0, 1, 2, -1
        ]
    }
})"
        )
    );
}