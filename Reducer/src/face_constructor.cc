// Created by D0000000000N

#include "../include/face.h"

Point3d Get3d(const std::pair<Point2d, double*>& point) {
    return {
        point.first.x,
        point.first.y,
        *point.second
    };
}

Point3d Get3d(Point2d point, double z) {
    return {
        point.x,
        point.y,
        z
    };
}

// Face::Face(const std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>>& point_vector_list) {
//     _origin = {0, 0, 0};
//     _normal = {0, 0, 0};

//     for (auto& e : point_vector_list) {
//         _points.push_back(e.first);
//         _origin += Get3d(e.first);
//         _normal += *e.second;
//     }

//     int points_count = point_vector_list.size();
//     _origin /= points_count;
//     _normal /= points_count;
//     _normal.Normalize();
    
// }

Face::Face(const std::map<Point2d, ReducerAttribute*>& sub_data) {
    _origin = {0, 0, 0};
    _normal = {0, 0, 0};

    for (auto&& [point, attribute] : sub_data) {
        _origin += Get3d(point, attribute->z);
        _normal += attribute->normal_vector;
    }

    int points_count = sub_data.size();
    _origin /= points_count;
    _normal /= points_count;
    _normal.Normalize();
    
    Rectangle rectangle;
    
    for (auto&& [point, _] : sub_data) {
        if (rectangle.min_x > point.x) {
            rectangle.min_x = point.x;
        }
        if (rectangle.max_x < point.x) {
            rectangle.max_x = point.x;
        }

        if (rectangle.min_y > point.y) {
            rectangle.min_y = point.y;
        }
        if (rectangle.max_y < point.y) {
            rectangle.max_y = point.y;
        }
    }

    _points_count = sub_data.size();
    _z_map = ZMap(sub_data, rectangle);
}
