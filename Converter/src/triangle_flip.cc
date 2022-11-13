// Created by 

#include "../include//triangle.h"

void Triangle::Flip() {
    int j0 = GetNeighborPointIndex(1);
    int j2 = (j0 + 2) % 3;

    Triangle* neighbor = neighbors[1];

    Point3d* point4 = neighbor->points[j2];

    // When edge `point1` - `point2` is illegal edge.
    if (this->GetCircumcircle().Contains(*point4)) {
        Point3d* point0 = points[0];
        Point3d* point1 = points[1];
        Point3d* point2 = points[2];

        Triangle* child0 = new Triangle(point0, point1, point4);
        Triangle* child2 = new Triangle(point0, point4, point2);

        children[0] = child0;
        children[2] = child2;

        int j1 = (j0 + 1) % 3;

        neighbor->children[j2] = child2;
        neighbor->children[j1] = child0;

        child0->neighbors[0] = neighbors[0];
        child0->neighbors[1] = neighbor->neighbors[j1];
        child0->neighbors[2] = child2;
        child0->neighbors[0] = child0;
        child0->neighbors[1] = neighbor->neighbors[j2];
        child0->neighbors[2] = neighbors[2];

        child0->Flip();
        child2->Flip();
    }
}