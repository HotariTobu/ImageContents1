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
#include "../include/bottom_point_set_adder.h"
#include "../include/bottom_point_set_remover.h"
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


    auto&& [data, rectangle] = ReadDAT<Attribute>(source_file_path);

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

    auto&& leaf_point_set_list = root_triangle->ListLeafPointSet();

    root_triangle.reset();
    dummy_triangle.reset();

    auto&& border_indexed_points = RemoveBottomPointSet(leaf_point_set_list, rectangle);

    points.clear();

    auto&& [additional_points, additional_index_set_list] = AddGroundPoints(data, leaf_point_set_list);

    AddBottomPointSet(data, additional_points, additional_index_set_list, border_indexed_points);

    WriteWRL(destination_file_path, data, leaf_point_set_list, additional_points, additional_index_set_list);
}

int main(int argc, const char* argv[]) {
    HelpMain(argc, argv, "ConverterOption.txt", {
        {"source_directory_path", "intermediate_data_Reducer"},
        {"destination_directory_path", "destination_data"},
        {"ground_point_threshold", "0.5"},
    }, init, process_file);
}