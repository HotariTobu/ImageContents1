// Created by D0000000000N

#include "../include/wrl_writer.h"

#include <fstream>

void WriteWRL(const std::string& path, const std::map<Point2d, Attribute>& data, Rectangle rectangle, const std::list<IndexedPoint2dSet>& point_set_list, const std::list<std::pair<Point2d, double>>& additional_points, const std::list<IndexSet>& additional_index_set_list) {
    std::ofstream ofs(path);

    ofs << R"(#VRML V2.0 utf8

Viewpoint {
)";

    double width = rectangle.max_x - rectangle.min_x;
    double height = rectangle.max_y - rectangle.min_y;

    Point2d center_point_2d = {
        (rectangle.max_x + rectangle.min_x) / 2,
        (rectangle.max_y + rectangle.min_y) / 2
    };

    Point2d camera_point_2d = {
        center_point_2d.x + width,
        center_point_2d.y - height
    };

    double camera_z = (camera_point_2d - center_point_2d).Length() * 0.8;

    ofs << "position " << camera_point_2d.x << ' ' << camera_z << ' ' << -camera_point_2d.y << std::endl;
    ofs << "orientation " << -0.7 << ' ' << 0.9 << ' ' << 0.3 << ' ' << 0.875 << std::endl;
    
    ofs << R"(}

Shape {
    appearance Appearance {
        material Material {}
    }
    geometry IndexedFaceSet {
        color Color {
            color [
)";

    for (auto e : data) {
        ofs << e.second.color << ',' << std::endl;
    }

    auto data_end = data.end();
    for (auto e : additional_points) {
        ofs << data.at(e.first).color << ',' << std::endl;
    }

    ofs << R"(            ]
        }
        coord Coordinate {
            point [
)";

    for (auto e : data) {
        ofs << e.first.x << ' ' << e.second.z << ' ' << -e.first.y << ',' << std::endl;
    }

    for (auto e : additional_points) {
        ofs << e.first.x << ' ' << e.second << ' ' << -e.first.y << ',' << std::endl;
    }

    ofs << R"(            ]
        }
        coordIndex [
)";

    for (auto e : point_set_list) {
        ofs << e[0].index << ", " << e[1].index << ", " << e[2].index << ", " << "-1" << std::endl;
    }

    for (auto e : additional_index_set_list) {
        ofs << e[0] << ", " << e[1] << ", " << e[2] << ", " << "-1" << std::endl;
    }

    ofs << R"(        ]
    }
})";

    ofs.close();
}
