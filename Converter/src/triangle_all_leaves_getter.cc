// Created by HotariTobu

#include "../include/triangle.h"

#include <stack>

std::vector<std::weak_ptr<Triangle>> Triangle::GetAllLeaves() const {
    std::vector<std::weak_ptr<Triangle>> leaves;

    std::stack<std::weak_ptr<Triangle>> triangle_stack;
    triangle_stack.push(std::const_pointer_cast<Triangle>(shared_from_this()));

    while (!triangle_stack.empty()) {
        auto triangle = triangle_stack.top().lock();
        triangle_stack.pop();

        if (!triangle->HasChild()) {
            leaves.push_back(triangle);
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            auto child = triangle->children[i];
            if (child != nullptr) {
                triangle_stack.push(child);
            }
        }
    }

    return leaves;
}