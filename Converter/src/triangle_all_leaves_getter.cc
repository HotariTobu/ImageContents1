// Created by HotariTobu

#include "../include/triangle.h"

#include <stack>

std::set<Triangle*> Triangle::GetAllLeaves() const {
    std::set<Triangle*> leaves;

    std::stack<Triangle*> triangle_stack;
    triangle_stack.push((Triangle*)this);

    while (!triangle_stack.empty()) {
        Triangle* triangle = triangle_stack.pop();

        if (!triangle->HasChild()) {
            leaves.insert(triangle);
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            Triangle* child = triangle->children[i];
            if (child != nullptr) {
                triangle_stack.push(child);
            }
        }
    }

    return leaves;
}