// Created by HotariTobu

#include "../include/triangle.h"

#include <stack>

std::list<IndexedPointSet> Triangle::ListLeafPointSet() const {
    std::list<IndexedPointSet> leaf_point_set_list;

    std::stack<std::weak_ptr<Triangle>> triangle_stack;
    triangle_stack.push(std::const_pointer_cast<Triangle>(shared_from_this()));

    while (!triangle_stack.empty()) {
        auto triangle = triangle_stack.top().lock();
        triangle_stack.pop();

        if (!triangle->HasChild()) {
            leaf_point_set_list.push_back(triangle->points);
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            auto child = triangle->children[i];
            if (child != nullptr) {
                triangle_stack.push(child);
            }
        }
    }

    return leaf_point_set_list;
}