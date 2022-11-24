// Created by D0000000000N

#include "../include/face.h"

Face::Face(const std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>>& point_vector_list) {
    _origin = {0, 0, 0};
    _normal = {0, 0, 0};

    for (auto& e : point_vector_list) {
        _points.push_back(e.first);
        _origin += e.first;
        _normal += *e.second;
    }

    int points_count = point_vector_list.size();
    _origin /= points_count;
    _normal /= points_count;
    _normal.Normalize();
    
}
