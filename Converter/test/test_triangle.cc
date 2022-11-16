// Created by 

#include <cassert>
#include <set>

#include "../include/triangle.h"
#include "near.h"

int main() {
    Point3d p0 = {0, 0, 0};
    Point3d p1 = {3, 0, 0};
    Point3d p2 = {0, 3, 0};

    Point3d p3 = {1, 1, 0};
    Point3d p4 = {0.6, 0.6, 0};
    Point3d p5 = {3, 3, 0};

    Triangle t1(&p0, &p1, &p2);

    Circle incircle = t1.GetIncircle();
    Circle circumcircle = t1.GetCircumcircle();

    assert(Near(incircle.center, {0.878679656440357, 0.878679656440357, 0}) && Near(incircle.radius, 0.87867965644));
    assert(Near(circumcircle.center, {1.5, 1.5, 0}) && Near(circumcircle.radius, 2.12132034356));

    assert(t1.Contains(&p3));

    Triangle t2(&p4, &p0, &p1);
    Triangle t3(&p4, &p1, &p2);
    Triangle t4(&p4, &p2, &p0);

    t1.children[0] = &t2;
    t1.children[1] = &t3;
    t1.children[2] = &t4;

    assert(&t3 == t1.FindDeepest(&p3));

    Triangle t5(&p0, &p1, &p2);
    Triangle t6(&p5, &p1, &p2);

    t1.neighbors[1] = &t6;
    t5.neighbors[1] = &t6;

    t1.children[1]->neighbors[1] = &t6;

    t5.Divide(&p3);

    assert(t1 == t5);

    Triangle t7(&p1, &p3, &p5);
    Triangle t8(&p2, &p3, &p5);

    t1.children[1]->children[0] = &t7;
    t1.children[1]->children[1] = &t8;
    t1.neighbors[1]->children[0] = &t7;
    t1.neighbors[1]->children[1] = &t8;

    t5.children[1]->Flip();

    assert(Near(t1, t5));

    std::set<Triangle*> leaves = {
        
    };

    assert(t5.GetAllLeaves() == leaves);
}