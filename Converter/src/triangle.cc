// Created by HotariTobu

#include "../include/triangle.h"

Triangle::Triangle(Point2d* p0, Point2d* p1, Point2d* p2) {
    points[0] = p0;
    points[1] = p1;
    points[2] = p2;
}

Triangle::~Triangle() {
}

bool Triangle::HasChild() const {
    for (int i = 0; i < 3; ++i) {
        if (children[i] != nullptr) {
            return true;
        }
    }
    
    return false;
}

bool HasSamePoints(const Triangle& triangle1, const Triangle& triangle2) {
    for (int i = 0; i < 3; ++i) {
        if (triangle1.points[i] != triangle2.points[i]) {
            return false;
        }
    }
    return true;
}

bool operator==(const Triangle& triangle1, const Triangle& triangle2) {
    for (int i = 0; i < 3; ++i) {
        if (triangle1.points[i] != triangle2.points[i]) {
            return false;
        }

        auto child1 = triangle1.children[i];
        auto child2 = triangle2.children[i];

        bool child1_not_null = child1 != nullptr;
        bool child2_not_null = child2 != nullptr;
        if (child1_not_null ^ child2_not_null) {
            return false;
        }
        if (child1_not_null && child2_not_null && *child1 != *child2) {
            return false;
        }

        auto neighbor1 = triangle1.neighbors[i].lock();
        auto neighbor2 = triangle2.neighbors[i].lock();

        bool neighbor1_not_null = neighbor1 != nullptr;
        bool neighbor2_not_null = neighbor2 != nullptr;
        if (neighbor1_not_null ^ neighbor2_not_null) {
            return false;
        }
        if (neighbor1_not_null && neighbor2_not_null && !HasSamePoints(*neighbor1, *neighbor2)) {
            return false;
        }
    }
    
    return true;
}

bool operator!=(const Triangle& triangle1, const Triangle& triangle2) {
    return !(triangle1 == triangle2);
}