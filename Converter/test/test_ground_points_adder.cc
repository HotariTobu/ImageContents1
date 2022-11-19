// Created by 

#include <cassert>
#include <filesystem>
#include <limits>
#include <set>

#include "point3d.h"
#include "../include/ground_points_adder.h"
#include "../include/index_set.h"
#include "../include/wrl_writer.h"

extern double ground_point_threshold;

Map2d<std::pair<double, PointType>> GetPointTypeMap(const std::vector<Point3d>& points) {
    int min_x = std::numeric_limits<int>().max();
    int min_y = std::numeric_limits<int>().max();
    int max_x = std::numeric_limits<int>().min();
    int max_y = std::numeric_limits<int>().min();

    for (Point3d point : points) {
        if (min_x > point.x) {
            min_x = point.x;
        }
        else if (max_x < point.x) {
            max_x = point.x;
        }

        if (min_y > point.y) {
            min_y = point.y;
        }
        else if (max_y < point.y) {
            max_y = point.y;
        }
    }

    int width = max_x - min_x + 3;
    int height = max_y - min_y + 3;

    Map2d<std::pair<double, PointType>> result;
    result.x = min_x;
    result.y = min_y;
    result.data = std::vector<std::vector<std::pair<double, PointType>>>(height, std::vector<std::pair<double, PointType>>(width, {0, PointType::NONE}));

    return result;
}

bool CanPass(std::vector<Point3d> points, std::vector<IndexSet> indices, std::set<std::vector<Point3d>> answer) {
    int index_set_count = indices.size();
    auto point_types = GetPointTypeMap(points);

    std::vector<Point2d> points_2d(points.size());
    std::vector<double> z_values(points.size());
    for (int i = 0; i < points.size(); i++) {
        points_2d[i] = {
            points[i].x,
            points[i].y
        };
        z_values[i] = points[i].z;
    }

    WriteWRL("before.wrl", points_2d, z_values, indices, point_types);

    AddGroundPoints(points_2d, z_values, indices);

    points.clear();
    points.resize(z_values.size());
    for (int i = 0; i < points.size(); i++) {
        points[i] = {
            points_2d[i].x,
            points_2d[i].y,
            z_values[i]
        };
    }

    WriteWRL("after.wrl", points_2d, z_values, indices, point_types);

    std::filesystem::remove("before.wrl");
    std::filesystem::remove("after.wrl");

    std::set<std::vector<Point3d>> result;
    for (IndexSet index_set : indices) {
        std::vector<Point3d> point_set;

        for (int i = 0; i < 3; ++i) {
            point_set.push_back(points[index_set[i]]);
        }

        result.insert(point_set);
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