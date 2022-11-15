// Created by D0000000000N

#include "../include/wrl_writer.h"

#include <fstream>

void WriteWRL(std::string path, const PointSet &points, const std::vector<IndexSet> &indices, const Map2d<PointType> &point_types)
{

    std::ofstream ofs(path);

    ofs << R"(#VRML V2.0 utf8

Shape {
    geometry IndexedFaceSet {
        colorPerVertex TRUE
        color Color {
            color [
)";

    for (auto e : points) {
        std::string color;
        switch (point_types.data[e.y][e.x]) {
        case PointType::GROUND:
            color = "0 1 0";
            break;
        case PointType::BUILDING:
            color = "1 0 0";
            break;
        default:
            color = "0 0 0";
        }
        ofs << color << std::endl;
    }

    ofs << R"(            ]
        }
        coord Coordinate {
            point [
)";

    for (auto e : points) {
        ofs << e.x << ' ' << e.y << ' ' << e.z << ',' << std::endl;
    }

    ofs << R"(            ]
        }
        coordIndex [
)";

    for (auto e : indices) {
        ofs << e[0] << ' ' << e[1] << ' ' << e[2] << ',' << " -1" << std::endl;
    }

    ofs << R"(        ]
    }
})";

}
