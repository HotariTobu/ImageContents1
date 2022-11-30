// Created by HotariTobu

#include <iostream>
#include <set>
#include <string>
#include <cmath>

#include "attribute.h"
#include "dat.h"
#include "main_helper.h"
#include "point3d.h"
#include "../include/big_triangle_maker.h"
#include "../include/ground_points_adder.h"
#include "../include/indexed_point2d.h"
#include "../include/randomizer.h"
#include "../include/root_maker.h"
#include "../include/triangle.h"
#include "../include/wrl_writer.h"


#include <fstream>
#include "z_map.h"


extern double ground_point_threshold;

std::string filename_suffix;

void init(std::map<std::string, std::string> option) {
    std::string ground_point_threshold_str = option.at("ground_point_threshold");
    ground_point_threshold = std::stod(ground_point_threshold_str);

    filename_suffix += "_GRO" + ground_point_threshold_str;
}

void process_file(const std::string source_file_path, const std::string destination_base_path) {
    std::string destination_file_path = destination_base_path + filename_suffix + ".wrl";
    std::cout << "Converting: " << source_file_path << " > " << destination_file_path << std::endl;

/*
    auto&& [data, _] = ReadDAT<Attribute>(source_file_path);

    int data_size = data.size();
    if (data_size == 0) {
        return;
    }

    std::vector<IndexedPoint2d> points;
    points.reserve(data_size);
    
    int i = 0;
    for (auto&& [point_2d, _] : data) {
        IndexedPoint2d point;
        point.index = i++;
        point.point = &point_2d;
        points.push_back(point);
    }

    Randomize(points);

    auto&& [p0, p1, p2] = MakeBigTriangle(points);
    IndexedPoint2d b0 = {-1, &p0};
    IndexedPoint2d b1 = {-2, &p1};
    IndexedPoint2d b2 = {-3, &p2};
    
    auto&& [root_triangle, dummy_triangle] = MakeRoot(&b0, &b1, &b2);

    for (auto&& point : points) {
        root_triangle->Divide(&point);
    }

    auto leaf_point_set_list = root_triangle->ListLeafPointSet();

    root_triangle.reset();
    dummy_triangle.reset();

    points.clear();

    auto&& [additional_points, additional_index_set_list] = AddGroundPoints(data, leaf_point_set_list);

    WriteWRL(destination_file_path, data, leaf_point_set_list, additional_points, additional_index_set_list);
*/
    auto&& [data, rectangle] = ReadDAT<Attribute>(source_file_path);
    ZMap z_map(data, rectangle);

    int width = z_map.width;
    int height = z_map.height;

    std::ofstream ofs(destination_file_path);

    ofs << R"(#VRML V2.0 utf8

Shape {
    appearance Appearance {
        material Material {}
    }
    geometry PointSet {
        color Color {
            color [
)";

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            int index = z_map.GetIndex(x, y);
            Point2d point = z_map.GetPoint(index);
            auto ite = data.find(point);
            if (ite == data.end()) {
                continue;
            }
            auto attr = ite->second;
            std::string color;
            switch (attr.type) {
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
    }

    ofs << R"(            ]
        }
        coord Coordinate {
            point [
)";

    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            int index = z_map.GetIndex(x, y);
            Point2d point = z_map.GetPoint(index);
            auto ite = data.find(point);
            if (ite == data.end()) {
                continue;
            }
            auto attr = ite->second;
            ofs << x << ' ' << y << ' ' << attr.z << ',' << std::endl;
        }
    }

    ofs << R"(            ]
        }
    }
})";

}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "ConverterOption.txt", {
        {"source_directory_path", "intermediate_data_Reducer"},
        {"destination_directory_path", "destination_data"},
        {"ground_point_threshold", "0.5"},
    }, init, process_file);
}