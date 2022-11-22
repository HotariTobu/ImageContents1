// Created by guinpen98

#include "../include//triangle.h"

bool Triangle::Contains(const IndexedPoint2d* point) const {
    bool signs[3];
    for (int i = 0; i < 3; ++i) {
        Vector2d edge = **(points[(i + 1) % 3]) - **(points[i]);
        Vector2d vector_to_point = **point - **(points[i]);

        double cross = edge.Cross(vector_to_point);
        signs[i] = cross < 0;
    }
    
    return
        (signs[0] && signs[1] && signs[2]) ||
        !(signs[0] || signs[1] || signs[2]);
}