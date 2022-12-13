// Created by HotariTobu

#include <cassert>
#include <set>

#include "../include/face.h"

bool CanPass(const std::list<std::pair<Point3d, Vector3d>>& point_vector_list, std::set<Point2d> answer_deleted_points, std::set<Point3d> answer_rest_of_points) {
    std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>> point_vector_list_ref;
    for (auto&& [point, vector] : point_vector_list) {
        point_vector_list_ref.push_back({
            {
                {
                    point.x,
                    point.y
                },
                const_cast<double*>(&point.z)
            },
            &vector
        });
    }

    Face face(point_vector_list_ref);

    auto deleted_points = face.DeleteInsidePoints();
    auto rest_of_points = face.points();

    std::set<Point2d> result_deleted_points;
    std::set<Point3d> result_rest_of_points;

    for (auto&& point : deleted_points) {
        result_deleted_points.insert(point);
    }

    for (auto&& point : rest_of_points) {
        result_rest_of_points.insert({
            point.first.x,
            point.first.y,
            *point.second
        });
    }

    return result_deleted_points == answer_deleted_points && result_rest_of_points == answer_rest_of_points;
}


int main() {
    assert(CanPass({
        {{ 0,  0, 0}, {0, 0, 0}},
        {{ 1,  0, 0}, {0, 0, 0}},
        {{ 0,  1, 0}, {0, 0, 0}},
        {{ 0, -1, 0}, {0, 0, 0}},
        {{-1,  0, 0}, {0, 0, 0}},
    }, {
        {0, 0},
    }, {
        { 1,  0, 0},
        { 0,  1, 0},
        { 0, -1, 0},
        {-1,  0, 0},
    }));
}