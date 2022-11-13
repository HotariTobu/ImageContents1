// Created by 

#include <cassert>

#include "../include/triangle.h"
#include "near.h"

int main() {
    Point3d point0 = {0, 0, 0};
    Point3d point1 = {0, 3, 0};
    Point3d point2 = {3, 0, 0};

    Point3d point3 = {1, 1, 0};
    Point3d point4 = {0.6, 0.6, 0};
    Point3d point5 = {3, 3, 0};

    Triangle triangle1(&point0, &point1, &point2);

    Circle incircle = triangle1.GetIncircle();
    Circle circumcircle = triangle1.GetCircumcircle();

    assert(Near(incircle.center, {0.878679656440357, 0.878679656440357, 0}) && Near(incircle.radius, 0.87867965644));
    assert(Near(circumcircle.center, {1.5, 1.5, 0}) && Near(circumcircle.radius, 2.12132034356));

    assert(triangle1.Contains(&point3));

    Triangle triangle2(&point4, &point0, &point1);
    Triangle triangle3(&point4, &point1, &point2);
    Triangle triangle4(&point4, &point2, &point0);

    triangle1.children[0] = &triangle2;
    triangle1.children[1] = &triangle3;
    triangle1.children[2] = &triangle4;

    assert(&triangle3 == triangle1.FindDeepest(&point3));

    Triangle triangle5(&point0, &point1, &point2);
    Triangle triangle6(&point5, &point1, &point2);

    triangle1.neighbors[1] = &triangle6;
    triangle5.neighbors[1] = &triangle6;

    triangle1.children[1]->neighbors[1] = &triangle6;

    triangle5.Divide(&point3);

    assert(triangle1 == triangle5);

    Triangle triangle7(&point1, &point3, &point5);
    Triangle triangle8(&point2, &point3, &point5);

    triangle1.children[1]->children[0] = &triangle7;
    triangle1.children[1]->children[1] = &triangle8;
    triangle1.neighbors[1]->children[0] = &triangle7;
    triangle1.neighbors[1]->children[1] = &triangle8;

    triangle5.children[1]->Flip();

    assert(Near(triangle1, triangle5));
}