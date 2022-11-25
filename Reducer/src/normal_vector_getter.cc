// Created by guinpen98

#include "../include/normal_vector_getter.h"

#include <vector>
#include <cmath>

Vector3d GetNormalVectorIn(Neighbor<ReducerAttribute> neighbor) {
    Vector3d normal_vector{0.0, 0.0, 0.0};

#ifdef __4_NEIGHBOR
    // 4-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{1, 2}, {0, 1}, {1, 0}, {2, 1}};
    const int edge_num = 4;
#elif __8_NEIGHBOR
    // 8-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {0, 1}};
    const int edge_num = 8;

#endif
    ReducerAttribute attribute;
    if (!neighbor.At(0, 0, &attribute)) {
        return normal_vector;
    }
    double center_z = attribute.z;

    std::vector<Vector3d> v(edge_num);
    for(int i = 0; i < edge_num; ++i){
        v[i].x = points[i].first - 1;
        v[i].y = points[i].second - 1;
        if (neighbor.At(points[i].first - 1, points[i].second - 1, &attribute)) {
            v[i].z = attribute.z - center_z;
        }
        else {
            v[i].z = std::nan("");
        }
    }
    for(int i = 0; i < edge_num; ++i){
        int j = (i + 1) % edge_num;
        if(std::isnan(v[i].z) || std::isnan(v[j].z)){
            continue;
        }
        normal_vector += v[i].Cross(v[j]);
    }
    normal_vector.Normalize();
    return normal_vector;
}