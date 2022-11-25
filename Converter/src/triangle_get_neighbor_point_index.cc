// Created by HotariTobu

#include "../include/triangle.h"

int Triangle::GetNeighborPointIndex(int neighbor_index) {
    auto point = points[neighbor_index];
    auto neighbor = neighbors[neighbor_index].lock();

    int j0 = 0;
    for (; neighbor->points[j0] != point; ++j0);

    return (j0 + 1) % 3;
}