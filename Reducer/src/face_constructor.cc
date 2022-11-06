// Created by D0000000000N

#include "../include/face.h"

Face::Face(const PointVectorSet& set) {

    _points = set.first;
    f_size = set.first.size();
    s_size = set.second.size();
    f_sum = 0;
    s_sum = 0;
    for (int i = 0; i < f_size; ++i) {
        f_sum += i;
    }
    for (int i = 0; i < s_size; ++i) {
        s_sum += i;
    }
    _origin = f_sum / f_size;
    _normal = s_sum / s_size;

}
