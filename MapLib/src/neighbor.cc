// Created by HotariTobu

#include "../include/neighbor.h"

#include "equals.h"

bool operator==(const Neighbor neighbor1, const Neighbor neighbor2) {
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (!Equals(neighbor1.data[y][x], neighbor2.data[y][x])) {
                return false;
            }
        }
    }

    return true;
}

bool operator!=(const Neighbor neighbor1, const Neighbor neighbor2) {
    return !(neighbor1 == neighbor2);
}
