// Created by guinpen98

#include "../include/face.h"

void Face::ProjectPoints() {
    // for(auto& point : _points){
    //     *point.second = _origin.z - (((point.first.x - _origin.x) * _normal.x + (point.first.y - _origin.y) * _normal.y) / _normal.z);
    // }

    Point2d base_point = {_z_map.rectangle.min_x, _z_map.rectangle.min_y};
    for (int i = 0; i < _z_map.size; ++i) {
        auto attribute = _z_map.z_values[i];
        if (attribute != nullptr) {
            Point2d point = _z_map.GetPoint(i) + base_point;
            (*attribute)->z = _origin.z - (((point.x - _origin.x) * _normal.x + (point.y - _origin.y) * _normal.y) / _normal.z);
        }
    }
}