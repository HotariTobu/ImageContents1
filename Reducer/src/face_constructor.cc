// Created by D0000000000N

#include "../include/face.h"

Face::Face(const PointVectorSet& set) {

    for (auto& e : set) {
        _points.push_back(e.first);
        _origin += e.first;
        _normal += e.second;
    }
    _origin /= set.size();
    _normal /= set.size();
    _normal.Normalize();
    
}
