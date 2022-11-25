// Created by HotariTobu

#include <cassert>

#include "../include/face.h"

template<typename T>
bool Near(const T& c1, const T& c2) {
    auto e1 = std::end(c1);
    auto e2 = std::end(c2);
    for (auto i1 = std::begin(c1), i2 = std::begin(c2); i1 != e1 && i2 != e2; ++i1, ++i2) {
        if (!Near(*i1, *i2)) {
            return false;
        }
    }
    return true;
}

bool CanPass(const std::list<std::pair<Point3d, Vector3d>>& point_vector_list, std::list<Point3d> answer) {
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
    face.ProjectPoints();

    auto points = face.points();

    std::list<Point3d> result;
    for (auto&& point : points) {
        result.push_back({
            point.first.x,
            point.first.y,
            *point.second
        });
    }
    
    return Near(result, answer);
}

int main() {
    assert(CanPass({
        {{ 1,  1,  0}, {0.57735 , 0.57735 , 0.57735 }},
        {{ 1, -1, -1}, {0.408248, 0.408248, 0.816497}},
        {{-1,  1,  1}, {0.408248, 0.816497, 0.408248}},
        {{-1, -1,  0}, {0.816497, 0.408248, 0.408248}},
    }, {
        { 1,  1, -2},
        { 1, -1,  0},
        {-1,  1,  0},
        {-1, -1,  2},
    }));
}