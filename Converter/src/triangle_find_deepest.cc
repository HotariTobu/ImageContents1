// Created by HotariTobu

#include "../include//triangle.h"

Triangle* Triangle::FindDeepest(Point3d* point) const {
    Triangle* triangle = (Triangle*)this;

    while (triangle->HasChild()) {
        for (int i = 0; i < 3; ++i) {
            if (triangle->children[i]->Contains(point)) {
                triangle = triangle->children[i];
                break;
            }
        }
    }

    return triangle;
}