// Created by 

#include <cassert>
#include <filesystem>

#include "point3d.h"
#include "../include/ground_points_adder.h"
#include "../include/index_set.h"
#include "../include/wrl_writer.h"

extern double ground_point_threshold;

IndexedPoint2d MakePoint(double x, double y) {
    static int index = 0;
    auto raw_point = new Point2d;
    raw_point->x = x;
    raw_point->y = y;
    return {index++, raw_point};
}

bool CanPass(const std::vector<Point3d>& points_3d, const std::vector<IndexSet>& index_set_list, const std::vector<std::vector<Point3d>>& answer) {
    std::map<Point2d, Attribute> data;

    int points_count = points_3d.size();
    std::vector<IndexedPoint2d> points;
    points.reserve(points_count);

    for (auto&& point_3d : points_3d) {
        Point2d point_2d = {
            point_3d.x,
            point_3d.y,
        };

        Attribute attribute;
        attribute.type = PointType::NONE;
        attribute.z = point_3d.z;

        auto [pair, _] = data.insert({point_2d, attribute});

        IndexedPoint2d point;
        point.point = &(*pair).first;
        points.push_back(point);
    }

    for (int i = 0; i < points_count; i++) {
        points[i].index = i;
    }
    
    std::list<IndexedPoint2dSet> point_set_list;

    for (auto &&index_set : index_set_list) {
        IndexedPoint2dSet point_set;
        for (int i = 0; i < 3; i++) {
            point_set[i] = &points[index_set[i]];
        }
        
    }


    WriteWRL("before.wrl", data, point_set_list);
    
    auto [additional_points, additional_index_set_list] = AddGroundPoints(data, point_set_list);

    WriteWRL("after.wrl", data, point_set_list, additional_points, additional_index_set_list);

    std::filesystem::remove("before.wrl");
    std::filesystem::remove("after.wrl");

    std::vector<std::vector<Point3d>> result;
    result.reserve(point_set_list.size() + additional_index_set_list.size());

    int data_size = data.size();
    auto additional_points_vector_edition = std::vector(additional_points.begin(), additional_points.end());

    for (auto&& point_set : point_set_list) {
        std::vector<Point3d> raw_point_set;

        for (int i = 0; i < 3; ++i) {
            IndexedPoint2d point = *(point_set[i]);
            Point3d point_3d;

            if (point.index < data_size) {
                Point2d point_2d = *const_cast<Point2d*>(point.point);
                point_3d.x = point_2d.x;
                point_3d.y = point_2d.y;
                point_3d.z = data.at(point_2d).z;
            }
            else {
                auto [point_2d, z] = additional_points_vector_edition[point.index - data_size];
                point_3d.x = point_2d.x;
                point_3d.y = point_2d.y;
                point_3d.z = z;
            }

            raw_point_set[i] = point_3d;
        }

        result.push_back(raw_point_set);
    }
    
    return result == answer;
}

int main() {
    ground_point_threshold = 0.5;

    assert(CanPass(
        {
            {2, 1, 2},
            {0, 1, 2},
            {2, 3, 2},
            {0, 3, 2},
            {2, 0, 0},
            {3, 1, 0},
        },
        {
            {0, 5, 2},
            {0, 2, 3},
            {0, 3, 1},
            {0, 1, 4},
            {0, 4, 5},
        },
        {
            {
                {2, 1, 0},
                {3, 1, 0},
                {2, 3, 2},
            },
            {
                {2, 1, 2},
                {2, 3, 2},
                {0, 3, 2},
            },
            {
                {2, 1, 2},
                {0, 3, 2},
                {0, 1, 2},
            },
            {
                {2, 1, 0},
                {0, 1, 2},
                {2, 0, 0},
            },
            {
                {2, 1, 0},
                {2, 0, 0},
                {3, 1, 0},
            },
            {
                {2, 1, 0},
                {2, 3, 2},
                {2, 1, 2},
            },
            {
                {2, 1, 0},
                {2, 1, 2},
                {0, 1, 2},
            },
        }
    ));
}