// Created by HotariTobu

#include <cassert>

#include "near.h"
#include "random.h"
#include "../include/triangle.h"

int main() {
    Random random(0, 1);

    Point2d p0 = {0, 0};
    Point2d p1 = {3, 0};
    Point2d p2 = {0, 3};

    Point2d p3 = {1, 1};
    Point2d p4 = {8, 8};
    Point2d p5 = {1.5, 1.5};

    auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
    
    Circle incircle = r1->GetIncircle();
    Circle circumcircle = r1->GetCircumcircle();

    assert(Near(incircle.center, {0.878679656440357, 0.878679656440357}) && Near(incircle.radius, 0.87867965644));
    assert(Near(circumcircle.center, {1.5, 1.5}) && Near(circumcircle.radius, 2.12132034356));
}