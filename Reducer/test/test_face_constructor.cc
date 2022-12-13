// Created by HotariTobu

#include <cassert>

#include "../include/face.h"

bool CanPass(const std::list<std::pair<Point3d, Vector3d>>& point_vector_list, Point3d origin, Vector3d normal) {
    std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>> point_vector_list_ref;
    std::set<std::pair<Point2d, double *>> points;
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
        points.insert(point_vector_list_ref.back().first);
    }

    Face face(point_vector_list_ref);

    return Near(face.origin(), origin) && Near(face.normal(), normal) && face.points() == points;
}

int main() {
    assert(CanPass({
        {{ 1.0,  1.0, -1.0}, {0.57735 , 0.57735 , 0.57735 }},
        {{ 1.0, -1.0,  0.0}, {0.408248, 0.408248, 0.816497}},
        {{-1.0,  1.0,  0.0}, {0.408248, 0.816497, 0.408248}},
        {{-1.0, -1.0,  1.0}, {0.816497, 0.408248, 0.408248}},
    }, {0, 0, 0}, {0.57735, 0.57735, 0.57735}));
}