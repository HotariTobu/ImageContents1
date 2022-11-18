// Created by HotariTobu

#include "../include//triangle.h"

/*
Determine if a point is on a line segment.
[params]
- point1: first point that consists the line segment
- point2: second point that consists the line segment
- point: a point that is determined if it is between `point1` and `point2`
[return]
Return true if `point` is on the segment other else false.
*/
bool IsBetween(Point3d point1, Point3d point2, Point3d point) {
    if ((point1.x <= point.x && point.x <= point2.x) || (point2.x <= point.x && point.x <= point1.x)) {
        if ((point1.y <= point.y && point.y <= point2.y) || (point2.y <= point.y && point.y <= point1.y)) {
            if ((point.y * (point1.x - point2.x)) + (point1.y * (point2.x - point.x)) + (point2.y * (point.x - point1.x)) == 0) {
                return true;
            }
        }
    }
    
    return false;
}

void Triangle::Divide(Point3d* point) {
    auto deepest = FindDeepest(point).lock();

    for (int i0 = 0; i0 < 3; ++i0) {
        int i1 = (i0 + 1) % 3;
        int i2 = (i0 + 2) % 3;

        Point3d* point0 = deepest->points[i0];
        Point3d* point1 = deepest->points[i1];

        if (IsBetween(*(point0), *(point1), *point)) {
            auto neighbor = deepest->neighbors[i0].lock();
            
            int j2 = deepest->GetNeighborPointIndex(i0);
            int j0 = (j2 + 1) % 3;
            int j1 = (j2 + 2) % 3;

            Point3d* point2 = deepest->points[i2];
            Point3d* point4 = neighbor->points[j2];

            auto child1 = std::make_shared<Triangle>(point, point1, point2);
            auto child2 = std::make_shared<Triangle>(point, point2, point0);
            auto neighbor1 = std::make_shared<Triangle>(point, point0, point4);
            auto neighbor2 = std::make_shared<Triangle>(point, point4, point1);

            deepest->children[i1] = child1;
            deepest->children[i2] = child2;
            neighbor->children[j1] = neighbor1;
            neighbor->children[j2] = neighbor2;

            child1->neighbors[0] = neighbor2;
            child1->neighbors[1] = deepest->neighbors[i1];
            child1->neighbors[2] = child2;
            child2->neighbors[0] = child1;
            child2->neighbors[1] = deepest->neighbors[i2];
            child2->neighbors[2] = neighbor1;
            neighbor1->neighbors[0] = child2;
            neighbor1->neighbors[1] = neighbor->neighbors[j1];
            neighbor1->neighbors[2] = neighbor2;
            neighbor2->neighbors[0] = neighbor1;
            neighbor2->neighbors[1] = neighbor->neighbors[j2];
            neighbor2->neighbors[2] = child1;

            child1->UpdateNeighbor(1);
            child2->UpdateNeighbor(1);
            neighbor1->UpdateNeighbor(1);
            neighbor2->UpdateNeighbor(1);

            child1->Flip();
            child2->Flip();
            neighbor1->Flip();
            neighbor2->Flip();

            return;
        }
    }

    {
        for (int i0 = 0; i0 < 3; ++i0) {
            int i1 = (i0 + 1) % 3;

            Point3d* point0 = deepest->points[i0];
            Point3d* point1 = deepest->points[i1];

            auto child = std::make_shared<Triangle>(point, point0, point1);

            deepest->children[i0] = child;
        }

        for (int i0 = 0; i0 < 3; ++i0) {
            int i1 = (i0 + 1) % 3;
            int i2 = (i0 + 2) % 3;
            
            auto child = deepest->children[i0];

            child->neighbors[0] = deepest->children[i2];
            child->neighbors[1] = deepest->neighbors[i0];
            child->neighbors[2] = deepest->children[i1];

            child->UpdateNeighbor(1);

            child->Flip();
        }
    }
}