// Created by HotariTobu

#include "../include/triangle.h"

int Triangle::GetNeighborPointIndex(int neighbor_index) {
    Point2d* point = points[neighbor_index];
    auto neighbor = neighbors[neighbor_index].lock();

    int j0 = 0;
    for (; neighbor->points[j0] != point; ++j0);

    int j1 = (j0 + 1) % 3;
    // if (neighbor->points[j1] == points[(neighbor_index + 1) % 3]) {
    //     return (j0 + 2) % 3;
    // }

    return j1;
}