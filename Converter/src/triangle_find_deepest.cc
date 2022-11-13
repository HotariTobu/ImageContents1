// Created by HotariTobu

#include "../include//triangle.h"

Triangle* Triangle::FindDeepest(Point3d* point) const {
    Triangle* triangle = (Triangle*)this;

    for (int i = 0; i < 3; ++i) {
        Triangle* child = triangle->children[i];
        if (child != nullptr && child->Contains(point)) {
            triangle = child;
            i = 0;
        }
    }

    return triangle;
}