// Created by 

#include "../include/triangle.h"

#include <set>

#include "near.h"

Triangle::Triangle(Point3d* p0, Point3d* p1, Point3d* p2) {
    points[0] = p0;
    points[1] = p1;
    points[2] = p2;

    for (int i = 0; i < 3; ++i) {
        children[i] = nullptr;
        neighbors[i] = nullptr;
    }
}

Triangle::~Triangle() {
    for (int i = 0; i < 3; ++i) {
        delete children[i];
    }
}

bool Triangle::HasChild() const {
    for (int i = 0; i < 3; ++i) {
        if (children[i] != nullptr) {
            return true;
        }
    }
    
    return false;
}

bool operator==(Triangle triangle1, Triangle triangle2) {
    if (
        triangle1.points[0] != triangle2.points[0] ||
        triangle1.points[1] != triangle2.points[1] ||
        triangle1.points[2] != triangle2.points[2]
    ) {
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        if (
            !((triangle1.children[i] == nullptr ^ triangle2.children[i] == nullptr) || *(triangle1.children[i]) == *(triangle2.children[i])) ||
            !((triangle1.neighbors[i] == nullptr ^ triangle2.neighbors[i] == nullptr) || *(triangle1.neighbors[i]) == *(triangle2.neighbors[i]))
        ) {
            return false;
        }
    }
    
    return true;
}

bool Near(Triangle triangle1, Triangle triangle2) {
    if (std::set(std::begin(triangle1.points), std::end(triangle1.points)) != std::set(std::begin(triangle2.points), std::end(triangle2.points))) {
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        if (
            !((triangle1.children[i] == nullptr ^ triangle2.children[i] == nullptr) || Near(*(triangle1.children[i]), *(triangle2.children[i]))) ||
            !((triangle1.neighbors[i] == nullptr ^ triangle2.neighbors[i] == nullptr) || Near(*(triangle1.neighbors[i]), *(triangle2.neighbors[i])))
        ) {
            return false;
        }
    }
    
    return true;
}
