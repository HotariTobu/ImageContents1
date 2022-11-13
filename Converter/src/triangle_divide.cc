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
    Triangle* deepest = FindDeepest(point);

    for (int i0 = 0; i0 < 3; ++i0) {
        int i1 = (i0 + 1) % 3;
        int i2 = (i0 + 2) % 3;

        Point3d* point0 = deepest->points[i0];
        Point3d* point1 = deepest->points[i1];

        if (IsBetween(*(point0), *(point1), *point)) {
            Point3d* point2 = deepest->points[i2];

            Triangle* child1 = new Triangle(point, point1, point2);
            Triangle* child2 = new Triangle(point, point2, point0);

            deepest->children[i1] = child1;
            deepest->children[i2] = child2;

            child1->neighbors[1] = deepest->neighbors[i1];
            child1->neighbors[2] = child2;
            child2->neighbors[0] = child1;
            child2->neighbors[1] = deepest->neighbors[i2];

            child1->Flip();
            child2->Flip();

            Triangle* neighbor = deepest->neighbors[i0];
            if (neighbor != nullptr) {
                int j0 = 0;
                while (neighbor->neighbors[j0] != deepest) {
                    j0++;
                }

                int j1 = (j0 + 1) % 3;
                int j2 = (j0 + 2) % 3;

                Point3d* point4 = neighbor->points[j2];

                Triangle* neighbor1 = new Triangle(point, point0, point4);
                Triangle* neighbor2 = new Triangle(point, point4, point1);

                neighbor->children[j1] = neighbor1;
                neighbor->children[j2] = neighbor2;

                child1->neighbors[0] = neighbor2;
                child2->neighbors[2] = neighbor1;

                neighbor1->neighbors[0] = child2;
                neighbor1->neighbors[1] = neighbor->neighbors[j1];
                neighbor1->neighbors[2] = neighbor2;
                neighbor2->neighbors[0] = neighbor1;
                neighbor2->neighbors[1] = neighbor->neighbors[j2];
                neighbor2->neighbors[2] = child1;

                neighbor1->Flip();
                neighbor2->Flip();
            }

            return;
        }
    }

    {
        for (int i0 = 0; i0 < 3; ++i0) {
            int i1 = (i0 + 1) % 3;

            Point3d* point0 = deepest->points[i0];
            Point3d* point1 = deepest->points[i1];

            Triangle* child = new Triangle(point, point0, point1);

            deepest->children[i0] = child;
        }

        for (int i0 = 0; i0 < 3; ++i0) {
            int i1 = (i0 + 1) % 3;
            int i2 = (i0 + 2) % 3;
            
            Triangle* child = deepest->children[i0];

            child->neighbors[i0] = deepest->children[i2];
            child->neighbors[i1] = deepest->neighbors[i0];
            child->neighbors[i2] = deepest->children[i1];

            child->Flip();
        }
    }
}