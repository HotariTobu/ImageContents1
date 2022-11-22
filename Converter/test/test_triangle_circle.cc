// Created by HotariTobu

#include <cassert>

#include "near.h"
#include "../include/triangle.h"

IndexedPoint2d MakePoint(double x, double y) {
    static int index = 0;
    auto raw_point = new Point2d;
    raw_point->x = x;
    raw_point->y = y;
    return {index++, raw_point};
}

int main() {
    auto p0 = MakePoint(0, 0);
    auto p1 = MakePoint(3, 0);
    auto p2 = MakePoint(0, 3);

    auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
    
    Circle incircle = r1->GetIncircle();
    Circle circumcircle = r1->GetCircumcircle();

    assert(Near(incircle.center, {0.878679656440357, 0.878679656440357}) && Near(incircle.radius, 0.87867965644));
    assert(Near(circumcircle.center, {1.5, 1.5}) && Near(circumcircle.radius, 2.12132034356));
}