// Created by guinpen98

#include "../include/normal_vector_getter.h"

#include <vector>
#include <cmath>

Vector3d GetNormalVectorIn(Neighbor neighbor) {
    Vector3d normal_vector{0.0, 0.0, 0.0};

#ifdef __4_NEIGHBOR
    // 4-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{1, 2}, {2, 1}, {1, 0}, {0, 1}};
    const int edge_num = 4;
#elif __8_NEIGHBOR
    // 8-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}, {0, 0}};
    const int edge_num = 8;

#endif
    std::vector<Vector3d> v(edge_num);
    for(int i = 0; i < edge_num; ++i){
        v[i].y = points[i].first - 1;
        v[i].x = points[i].second - 1;
        v[i].z = std::isnan(neighbor.data[points[i].first][points[i].second]) ? std::nan("") : neighbor.data[points[i].first][points[i].second] - neighbor.data[1][1];
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