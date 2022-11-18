// Created by HotariTobu

#include "../include//triangle.h"

void Triangle::Flip() {
    int j2 = GetNeighborPointIndex(1);

    auto neighbor = neighbors[1].lock();

    Point3d* point4 = neighbor->points[j2];

    // When edge `point1` - `point2` is illegal edge.
    if (this->GetCircumcircle().Contains(*point4)) {
        int j1 = (j2 + 2) % 3;

        Point3d* point0 = points[0];
        Point3d* point1 = points[1];
        Point3d* point2 = points[2];

        auto child0 = std::make_shared<Triangle>(point0, point1, point4);
        auto child2 = std::make_shared<Triangle>(point0, point4, point2);

        children[0] = child0;
        children[2] = child2;
        neighbor->children[j2] = child2;
        neighbor->children[j1] = child0;

        child0->neighbors[0] = neighbors[0];
        child0->neighbors[1] = neighbor->neighbors[j1];
        child0->neighbors[2] = child2;
        child2->neighbors[0] = child0;
        child2->neighbors[1] = neighbor->neighbors[j2];
        child2->neighbors[2] = neighbors[2];

        child0->UpdateNeighbor(0);
        child0->UpdateNeighbor(1);
        child2->UpdateNeighbor(1);
        child2->UpdateNeighbor(2);

        child0->Flip();
        child2->Flip();
    }
}