// Created by D0000000000N

#include "../include/wrl_writer.h"

#include <fstream>

void WriteWRL(std::string path, const std::vector<Point2d>& points, const std::vector<double>& z_values, const std::vector<IndexSet>& indices, const Map2d<std::pair<double, PointType>>& point_types) {
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
        switch (point_types.data[e.y + 1][e.x + 1].second) {
        case PointType::GROUND:
            color = "0 1 0";
            break;
        case PointType::BUILDING:
            color = "1 0 0";
            break;
        default:
            color = "1 1 1";
        }
        ofs << color << ',' << std::endl;
    }

    ofs << R"(            ]
        }
        coord Coordinate {
            point [
)";

    for (int i = 0; i < points.size(); ++i) {
        ofs << points[i].x << ' ' << z_values[i] << ' ' << -points[i].y << ',' << std::endl;
    }

    ofs << R"(            ]
        }
        coordIndex [
)";

    for (auto e : indices) {
        ofs << e[0] << ", " << e[1] << ", " << e[2] << ", " << "-1" << std::endl;
    }

    ofs << R"(        ]
    }
})";

    ofs.close();
}
