// Created by HotariTobu

#include "../include/neighbor.h"

Neighbor::Neighbor(int stride) {
    this->stride = stride;
}

bool Neighbor::At(int x, int y, double* z) const {
    const double* pointer = head + x + y * stride;
    if (pointer == nullptr) {
        return false;
    }

    *z = *pointer;
    return true;
}

bool Neighbor::IsAllNull() const {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (head + x + y * stride != nullptr) {
                return false;
            }
        }
    }
    
    return true;
}

bool operator==(const Neighbor neighbor1, const Neighbor neighbor2) {
    return
        neighbor1.head == neighbor2.head &&
        neighbor1.stride == neighbor2.stride;
}

bool operator!=(const Neighbor neighbor1, const Neighbor neighbor2) {
    return !(neighbor1 == neighbor2);
}
