// Created by 

#include <cassert>
#include <random>
#include <set>

#include "../include/triangle.h"
#include "near.h"

std::default_random_engine random_engine;
std::uniform_real_distribution<double> random_distribution;

double Rand() {
    return random_distribution(random_engine);
}

int main() {
    std::random_device random_device;
    random_engine = std::default_random_engine(random_device());
    random_distribution = std::uniform_real_distribution<double>(-100, 100);

    Point3d p0 = {0, 0, Rand()};
    Point3d p1 = {3, 0, Rand()};
    Point3d p2 = {0, 3, Rand()};

    Point3d p3 = {1, 1, Rand()};
    Point3d p4 = {8, 8, Rand()};
    Point3d p5 = {1.5, 1.5, Rand()};

    {
        Triangle r1(&p0, &p1, &p2);
        r1.neighbors[0] = &r1;
        r1.neighbors[1] = &r1;
        r1.neighbors[2] = &r1;

        assert(!r1.HasChild());

        Circle incircle = r1.GetIncircle();
        Circle circumcircle = r1.GetCircumcircle();

        assert(Near(incircle.center, {0.878679656440357, 0.878679656440357, 0}) && Near(incircle.radius, 0.87867965644));
        assert(Near(circumcircle.center, {1.5, 1.5, 0}) && Near(circumcircle.radius, 2.12132034356));

        for (double x = 0.1; x < 3; x += 0.1) {
            Point3d p = {x, 0.1, Rand()};
            assert(r1.Contains(&p));
        }

        for (double y = 0.1; y < 3; y += 0.1) {
            Point3d p = {0.1, y, Rand()};
            assert(r1.Contains(&p));
        }

        for (double x = 0.1, y = 2.9; x < 3 && y > 0; x += 0.1, y -= 0.1) {
            Point3d p = {x, y, Rand()};
            assert(r1.Contains(&p));
        }
    }

    {
        Triangle r1(&p0, &p1, &p2);
        r1.neighbors[0] = &r1;
        r1.neighbors[1] = &r1;
        r1.neighbors[2] = &r1;

        Triangle n1(&p4, &p2, &p1);
        n1.neighbors[0] = &n1;
        n1.neighbors[1] = &n1;
        n1.neighbors[2] = &n1;

        r1.neighbors[1] = &n1;
        n1.neighbors[1] = &r1;

        Triangle c0(&p3, &p0, &p1);
        Triangle c1(&p3, &p1, &p2);
        Triangle c2(&p3, &p2, &p0);

        r1.children[0] = &c0;
        r1.children[1] = &c1;
        r1.children[2] = &c2;

        assert(r1.HasChild());

        assert(&c1 == r1.FindDeepest(&p3));

        c0.neighbors[0] = &c2;
        c0.neighbors[1] = &r1;
        c0.neighbors[2] = &c1;
        c1.neighbors[0] = &c0;
        c1.neighbors[1] = &n1;
        c1.neighbors[2] = &c2;
        c2.neighbors[0] = &c1;
        c2.neighbors[1] = &r1;
        c2.neighbors[2] = &c0;

        Triangle r2(&p0, &p1, &p2);
        r2.neighbors[0] = &r2;
        r2.neighbors[1] = &r2;
        r2.neighbors[2] = &r2;

        Triangle n2(&p4, &p2, &p1);
        n2.neighbors[0] = &n2;
        n2.neighbors[1] = &n2;
        n2.neighbors[2] = &n2;

        r2.neighbors[1] = &n2;
        n2.neighbors[1] = &r2;

        r2.Divide(&p3);

        assert(r1 == r2);

        p4.x = 3;
        p4.y = 3;

        Triangle c3(&p3, &p1, &p4);
        Triangle c4(&p3, &p4, &p2);

        c1.children[0] = &c3;
        c1.children[2] = &c4;
        n1.children[0] = &c4;
        n1.children[2] = &c3;

        c3.neighbors[0] = &c0;
        c3.neighbors[1] = &n1;
        c3.neighbors[2] = &c4;
        c4.neighbors[0] = &c3;
        c4.neighbors[1] = &n1;
        c4.neighbors[2] = &c2;

        r2.children[1]->Flip();

        assert(r1 == r2);
    }

    {
        Triangle r1(&p0, &p1, &p2);
        r1.neighbors[0] = &r1;
        r1.neighbors[1] = &r1;
        r1.neighbors[2] = &r1;

        Triangle n1(&p4, &p2, &p1);
        n1.neighbors[0] = &n1;
        n1.neighbors[1] = &n1;
        n1.neighbors[2] = &n1;

        r1.neighbors[1] = &n1;
        n1.neighbors[1] = &r1;

        Triangle c0(&p5, &p0, &p1);
        Triangle c2(&p5, &p2, &p0);
        Triangle c3(&p5, &p1, &p4);
        Triangle c4(&p5, &p4, &p2);

        r1.children[0] = &c0;
        r1.children[2] = &c2;
        n1.children[0] = &c4;
        n1.children[2] = &c3;

        c0.neighbors[0] = &c2;
        c0.neighbors[1] = &r1;
        c0.neighbors[2] = &c3;
        c2.neighbors[0] = &c4;
        c2.neighbors[1] = &r1;
        c2.neighbors[2] = &c0;
        c3.neighbors[0] = &c0;
        c3.neighbors[1] = &n1;
        c3.neighbors[2] = &c4;
        c4.neighbors[0] = &c3;
        c4.neighbors[1] = &n1;
        c4.neighbors[2] = &c2;

        Triangle r2(&p0, &p1, &p2);
        r2.neighbors[0] = &r2;
        r2.neighbors[1] = &r2;
        r2.neighbors[2] = &r2;

        Triangle n2(&p4, &p2, &p1);
        n2.neighbors[0] = &n2;
        n2.neighbors[1] = &n2;
        n2.neighbors[2] = &n2;

        r2.neighbors[1] = &n2;
        n2.neighbors[1] = &r2;

        r2.Divide(&p5);

        assert(r1 == r2);
    }

    {
        Triangle r2(&p0, &p1, &p2);
        r2.neighbors[0] = &r2;
        r2.neighbors[1] = &r2;
        r2.neighbors[2] = &r2;

        Triangle n2(&p4, &p2, &p1);
        n2.neighbors[0] = &n2;
        n2.neighbors[1] = &n2;
        n2.neighbors[2] = &n2;

        r2.neighbors[1] = &n2;
        n2.neighbors[1] = &r2;

        r2.Divide(&p3);

        std::set<Triangle*> leaves = {
            r2.children[0],
            r2.children[2],
            n2.children[0],
            n2.children[2],
        };

        assert(r2.GetAllLeaves() == leaves);
    }
}