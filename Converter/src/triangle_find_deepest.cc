// Created by HotariTobu

#include "../include//triangle.h"

std::weak_ptr<Triangle> Triangle::FindDeepest(Point2d* point) const {
    auto triangle = std::const_pointer_cast<Triangle>(shared_from_this());

    for (int i = 0; i < 3; ++i) {
        auto child = triangle->children[i];
        if (child != nullptr && child->Contains(point)) {
            triangle = child;
            i = -1;
        }
    }

    return triangle;
}