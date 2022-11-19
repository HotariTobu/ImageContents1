// Created by HotariTobu

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>

#include "near.h"
#include "random.h"
#include "../include/triangle.h"

template<typename T>
bool EqualsAsSet(T c1, T c2) {
    if (std::size(c1) != std::size(c2)) {
        return false;
    }
    
    for (auto e : c1) {
        auto last = std::end(c2);
        auto ite = std::find(std::begin(c2), last, e);
        if (ite == last) {
            return false;
        }
    }

    return true;
}

template<typename T>
std::vector<std::shared_ptr<T>> SharedCast(std::vector<std::weak_ptr<T>> container) {
    int elements_count = container.size();
    std::vector<std::shared_ptr<T>> result(elements_count);

    for (int i = 0; i < elements_count; ++i) {
        result[i] = container[i].lock();
    }

    return result;
}

std::string Describe(Triangle triangle) {
    std::stringstream stream;

    for (int i = 0; i < 3; i++) {
        Point2d point = *triangle.points[i];
        stream << '(' << (int)point.x << ", " << (int)point.y << "), ";
    }

    return stream.str();
}

int main() {
    Random random(-100, 100);

    Point2d p0 = {0, 0};
    Point2d p1 = {3, 0};
    Point2d p2 = {0, 3};

    Point2d p3 = {1, 1};
    Point2d p4 = {8, 8};
    Point2d p5 = {1.5, 1.5};

    {
        auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r1->neighbors[0] = r1;
        r1->neighbors[1] = r1;
        r1->neighbors[2] = r1;

        assert(!r1->HasChild());

        Circle incircle = r1->GetIncircle();
        Circle circumcircle = r1->GetCircumcircle();

        assert(Near(incircle.center, {0.878679656440357, 0.878679656440357}) && Near(incircle.radius, 0.87867965644));
        assert(Near(circumcircle.center, {1.5, 1.5}) && Near(circumcircle.radius, 2.12132034356));

        for (double x = 0.1; x < 3; x += 0.1) {
            Point2d p = {x, 0.1};
            assert(r1->Contains(&p));
        }

        for (double y = 0.1; y < 3; y += 0.1) {
            Point2d p = {0.1, y};
            assert(r1->Contains(&p));
        }

        for (double x = 0.1, y = 2.9; x < 3 && y > 0; x += 0.1, y -= 0.1) {
            Point2d p = {x, y};
            assert(r1->Contains(&p));
        }
    }

    {
        auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r1->neighbors[0] = r1;
        r1->neighbors[1] = r1;
        r1->neighbors[2] = r1;

        auto n1 = std::make_shared<Triangle>(&p4, &p2, &p1);
        n1->neighbors[0] = n1;
        n1->neighbors[1] = n1;
        n1->neighbors[2] = n1;

        r1->neighbors[1] = n1;
        n1->neighbors[1] = r1;

        auto c0 = std::make_shared<Triangle>(&p3, &p0, &p1);
        auto c1 = std::make_shared<Triangle>(&p3, &p1, &p2);
        auto c2 = std::make_shared<Triangle>(&p3, &p2, &p0);

        r1->children[0] = c0;
        r1->children[1] = c1;
        r1->children[2] = c2;

        assert(r1->HasChild());

        Point2d p6 = {1, 0.5};

        assert(*c0 == *r1->FindDeepest(&p6).lock());

        c0->neighbors[0] = c2;
        c0->neighbors[1] = r1;
        c0->neighbors[2] = c1;
        c1->neighbors[0] = c0;
        c1->neighbors[1] = n1;
        c1->neighbors[2] = c2;
        c2->neighbors[0] = c1;
        c2->neighbors[1] = r1;
        c2->neighbors[2] = c0;

        auto r2 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r2->neighbors[0] = r2;
        r2->neighbors[1] = r2;
        r2->neighbors[2] = r2;

        auto n2 = std::make_shared<Triangle>(&p4, &p2, &p1);
        n2->neighbors[0] = n2;
        n2->neighbors[1] = n2;
        n2->neighbors[2] = n2;

        r2->neighbors[1] = n2;
        n2->neighbors[1] = r2;

        r2->Divide(&p3);

        assert(*r1 == *r2);

        p4.x = 3;
        p4.y = 3;

        auto c3 = std::make_shared<Triangle>(&p3, &p1, &p4);
        auto c4 = std::make_shared<Triangle>(&p3, &p4, &p2);

        c1->children[0] = c3;
        c1->children[2] = c4;
        n1->children[0] = c4;
        n1->children[2] = c3;

        c3->neighbors[0] = c0;
        c3->neighbors[1] = n1;
        c3->neighbors[2] = c4;
        c4->neighbors[0] = c3;
        c4->neighbors[1] = n1;
        c4->neighbors[2] = c2;

        r2->children[1]->Flip();

        assert(*r1 == *r2);
    }

    {
        auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r1->neighbors[0] = r1;
        r1->neighbors[1] = r1;
        r1->neighbors[2] = r1;

        auto n1 = std::make_shared<Triangle>(&p4, &p2, &p1);
        n1->neighbors[0] = n1;
        n1->neighbors[1] = n1;
        n1->neighbors[2] = n1;

        r1->neighbors[1] = n1;
        n1->neighbors[1] = r1;

        auto c0 = std::make_shared<Triangle>(&p5, &p0, &p1);
        auto c2 = std::make_shared<Triangle>(&p5, &p2, &p0);
        auto c3 = std::make_shared<Triangle>(&p5, &p1, &p4);
        auto c4 = std::make_shared<Triangle>(&p5, &p4, &p2);

        r1->children[0] = c0;
        r1->children[2] = c2;
        n1->children[0] = c4;
        n1->children[2] = c3;

        c0->neighbors[0] = c2;
        c0->neighbors[1] = r1;
        c0->neighbors[2] = c3;
        c2->neighbors[0] = c4;
        c2->neighbors[1] = r1;
        c2->neighbors[2] = c0;
        c3->neighbors[0] = c0;
        c3->neighbors[1] = n1;
        c3->neighbors[2] = c4;
        c4->neighbors[0] = c3;
        c4->neighbors[1] = n1;
        c4->neighbors[2] = c2;

        auto r2 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r2->neighbors[0] = r2;
        r2->neighbors[1] = r2;
        r2->neighbors[2] = r2;

        auto n2 = std::make_shared<Triangle>(&p4, &p2, &p1);
        n2->neighbors[0] = n2;
        n2->neighbors[1] = n2;
        n2->neighbors[2] = n2;

        r2->neighbors[1] = n2;
        n2->neighbors[1] = r2;

        r2->Divide(&p5);

        assert(*r1 == *r2);
    }

    {
        auto r2 = std::make_shared<Triangle>(&p0, &p1, &p2);
        r2->neighbors[0] = r2;
        r2->neighbors[1] = r2;
        r2->neighbors[2] = r2;

        auto n2 = std::make_shared<Triangle>(&p4, &p2, &p1);
        n2->neighbors[0] = n2;
        n2->neighbors[1] = n2;
        n2->neighbors[2] = n2;

        r2->neighbors[1] = n2;
        n2->neighbors[1] = r2;

        r2->Divide(&p3);

        auto result_leaves = r2->GetAllLeaves();

        std::vector<std::weak_ptr<Triangle>> answer_leaves = {
            r2->children[0],
            r2->children[2],
            n2->children[0],
            n2->children[2],
        };

        assert(EqualsAsSet(SharedCast(result_leaves), SharedCast(answer_leaves)));
    }
}