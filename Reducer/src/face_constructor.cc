// Created by D0000000000N

#include "../include/face.h"

Point3d Get3d(const std::pair<Point2d, double*>& point) {
    return {
        point.first.x,
        point.first.y,
        *point.second
    };
}

Face::Face(const std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>>& point_vector_list) {
    _origin = {0, 0, 0};
    _normal = {0, 0, 0};

    for (auto& e : point_vector_list) {
        _origin += Get3d(e.first);
        _normal += *e.second;
        _points.insert({
            {
                (int)e.first.first.x,
                (int)e.first.first.y
            },
            e.first.second
        });
    }

    int points_count = point_vector_list.size();
    _origin /= points_count;
    _normal.Normalize();
}
