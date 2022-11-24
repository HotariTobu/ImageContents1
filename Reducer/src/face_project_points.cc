// Created by guinpen98

#include "../include/face.h"

void Face::ProjectPoints() {
    for(auto& point : _points){
        *point.second = _origin.z - (((point.first.x - _origin.x) * _normal.x + (point.first.y - _origin.y) * _normal.y) / _normal.z);
    }
}