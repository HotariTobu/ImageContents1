Created by HotariTobu

#include "../include/triangle.h"

int Triangle::GetNeighborPointIndex(int neighbor_index) {
    Triangle* neighbor = neighbors[neighbor_index];
    int j = 0;
    for (; neighbor->neighbors[j] != this; ++j);
    return j;
}