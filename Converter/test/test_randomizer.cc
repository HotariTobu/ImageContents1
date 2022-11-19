// Created by HotariTobu

#include <cassert>
#include <ctime>

#include "../include/randomizer.h"

bool CanPass() {
    constexpr int points_count = 20;
    std::vector<Point2d> points;

    for (int i = 0; i < points_count; i++) {
        Point2d point;
        point.x = rand();
        point.y = rand();
        points.push_back(point);
    }
    
    std::vector<Point2d> clone = points;

    Randomize(clone);

    return points != clone;
}

int main() {
    srand(std::time(NULL));

    for (int i = 0; i < 5; ++i) {
        assert(CanPass());
    }
}