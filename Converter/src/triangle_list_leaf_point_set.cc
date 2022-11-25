// Created by HotariTobu

#include "../include/triangle.h"

#include <stack>

std::list<IndexedPoint2dSet> Triangle::ListLeafPointSet() const {
    std::list<IndexedPoint2dSet> leaf_point_set_list;

    std::stack<std::weak_ptr<Triangle>> triangle_stack;
    triangle_stack.push(std::const_pointer_cast<Triangle>(shared_from_this()));

    while (!triangle_stack.empty()) {
        auto&& triangle = triangle_stack.top().lock();
        triangle_stack.pop();

        if (triangle->HasBeenScanned) {
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            auto&& child = triangle->children[i];
            if (child != nullptr) {
                triangle_stack.push(child);
                continue;
            }
        }

        triangle->HasBeenScanned = true;
        leaf_point_set_list.push_back({
            *const_cast<IndexedPoint2d*>(triangle->points[0]),
            *const_cast<IndexedPoint2d*>(triangle->points[1]),
            *const_cast<IndexedPoint2d*>(triangle->points[2]),
        });
    }

    return leaf_point_set_list;
}