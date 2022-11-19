// Created by HotariTobu

#include "../include/triangle.h"

void Triangle::UpdateNeighbor(int neighbor_index) {
    int j1 = GetNeighborPointIndex(neighbor_index);
    int j2 = (j1 + 1) % 3;

    auto neighbor = neighbors[neighbor_index].lock();
    neighbor->neighbors[j2] = shared_from_this();
}