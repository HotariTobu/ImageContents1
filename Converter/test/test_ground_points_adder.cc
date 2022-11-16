// Created by 

#include <cassert>
#include <filesystem>
#include <limits>
#include <set>

#include "../include/ground_points_adder.h"
#include "../include/index_set.h"
#include "../include/wrl_writer.h"

extern double ground_point_threshold;

Map2d<PointType> GetPointTypeMap(const PointSet& points) {
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

    Map2d<PointType> result;
    result.x = min_x;
    result.y = min_y;
    result.data = std::vector<std::vector<PointType>>(height, std::vector<PointType>(width, PointType::NONE));

    return result;
}

bool CanPass(PointSet points, std::vector<IndexSet> indices, std::set<std::vector<Point3d>> answer) {
    int index_set_count = indices.size();
    auto point_types = GetPointTypeMap(points);

    WriteWRL("before.wrl", points, indices, point_types);

    AddGroundPoints(points, indices);

    WriteWRL("after.wrl", points, indices, point_types);

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