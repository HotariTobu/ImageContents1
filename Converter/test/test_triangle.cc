// Created by HotariTobu

#include <algorithm>
#include <cassert>

#include "../include/root_maker.h"
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

    auto p3 = MakePoint(1, 1);
    auto p4 = MakePoint(8, 8);
    auto p5 = MakePoint(1.5, 1.5);

    {
        auto [r1, d0] = MakeRoot(&p0, &p1, &p2);

        assert(!r1->HasChild());
    }

    {
        auto r1 = std::make_shared<Triangle>(&p0, &p1, &p2);
        auto n1 = std::make_shared<Triangle>(&p1, &p4, &p2);

        r1->neighbors[1] = n1;
        r1->UpdateNeighbor(1);

        assert(r1->GetNeighborPointIndex(1) == 1);
        assert(n1->neighbors[2].lock() == r1);
    }

    {
        auto [r1, d0] = MakeRoot(&p0, &p1, &p2);
        auto [n1, d1] = MakeRoot(&p1, &p4, &p2);
        
        r1->neighbors[1] = n1;
        n1->neighbors[2] = r1;

        auto c0 = std::make_shared<Triangle>(&p3, &p0, &p1);
        auto c1 = std::make_shared<Triangle>(&p3, &p1, &p2);
        auto c2 = std::make_shared<Triangle>(&p3, &p2, &p0);

        r1->children[0] = c0;
        r1->children[1] = c1;
        r1->children[2] = c2;

        assert(r1->HasChild());

        auto p6 = MakePoint(1, 0.5);

        assert(*c0 == *r1->FindDeepest(&p6).lock());

        c0->neighbors[0] = c2;
        c0->neighbors[1] = d0;
        c0->neighbors[2] = c1;
        c1->neighbors[0] = c0;
        c1->neighbors[1] = n1;
        c1->neighbors[2] = c2;
        c2->neighbors[0] = c1;
        c2->neighbors[1] = d0;
        c2->neighbors[2] = c0;

        d0->neighbors[1] = c0;
        d0->neighbors[2] = c2;
        n1->neighbors[1] = c1;

        auto [r2, d2] = MakeRoot(&p0, &p1, &p2);
        auto [n2, d3] = MakeRoot(&p2, &p1, &p4);
        
        r2->neighbors[1] = n2;
        n2->neighbors[0] = r2;

        r2->Divide(&p3);

        assert(*r1 == *r2);

        const_cast<Point2d*>(p4.point)->x = 3;
        const_cast<Point2d*>(p4.point)->y = 3;

        auto c3 = std::make_shared<Triangle>(&p3, &p1, &p4);
        auto c4 = std::make_shared<Triangle>(&p3, &p4, &p2);

        c1->children[0] = c3;
        c1->children[2] = c4;
        n1->children[0] = c4;
        n1->children[2] = c3;

        c3->neighbors[0] = c0;
        c3->neighbors[1] = d1;
        c3->neighbors[2] = c4;
        c4->neighbors[0] = c3;
        c4->neighbors[1] = d1;
        c4->neighbors[2] = c2;

        c0->neighbors[2] = c3;
        d1->neighbors[0] = c3;
        d1->neighbors[2] = c4;
        c2->neighbors[0] = c4;

        r2->children[1]->Flip();

        assert(*r1 == *r2);
    }

    {
        auto [r1, d0] = MakeRoot(&p0, &p1, &p2);
        auto [n1, d1] = MakeRoot(&p1, &p4, &p2);
        
        r1->neighbors[1] = n1;
        n1->neighbors[2] = r1;

        auto c0 = std::make_shared<Triangle>(&p5, &p0, &p1);
        auto c2 = std::make_shared<Triangle>(&p5, &p2, &p0);
        auto c3 = std::make_shared<Triangle>(&p5, &p1, &p4);
        auto c4 = std::make_shared<Triangle>(&p5, &p4, &p2);

        r1->children[0] = c0;
        r1->children[2] = c2;
        n1->children[0] = c3;
        n1->children[1] = c4;

        c0->neighbors[0] = c2;
        c0->neighbors[1] = d0;
        c0->neighbors[2] = c3;
        c2->neighbors[0] = c4;
        c2->neighbors[1] = d0;
        c2->neighbors[2] = c0;
        c3->neighbors[0] = c0;
        c3->neighbors[1] = n1;
        c3->neighbors[2] = c4;
        c4->neighbors[0] = c3;
        c4->neighbors[1] = n1;
        c4->neighbors[2] = c2;

        auto [r2, d2] = MakeRoot(&p0, &p1, &p2);
        auto [n2, d3] = MakeRoot(&p1, &p4, &p2);
        
        r2->neighbors[1] = n2;
        n2->neighbors[2] = r2;

        r2->Divide(&p5);

        assert(*r1 == *r2);
    }
}