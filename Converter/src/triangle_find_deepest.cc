// Created by HotariTobu

#include "../include//triangle.h"

const Triangle* Triangle::FindDeepest(Point3d* point) const {
    const Triangle* triangle = this;

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