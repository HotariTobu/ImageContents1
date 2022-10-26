// Created by 

#include "../include/face.h"

void Face::ProjectPoints() {
    for(auto& point : _points){
        point.y = _origin.z - ((point.x - _origin.x) * _normal.x + (point.y - _origin.y) * _normal.y) / _normal.z;
    }
}