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

int main() {
    auto p0 = MakePoint(0, 0);
    auto p1 = MakePoint(3, 0);
    auto p2 = MakePoint(0, 3);

    auto p3 = MakePoint(1, 1);
    auto p4 = MakePoint(3, 3);

    auto [r2, d0] = MakeRoot(&p0, &p1, &p2);
    auto [n2, d1] = MakeRoot(&p1, &p4, &p2);

    r2->neighbors[1] = n2;
    n2->neighbors[2] = r2;

    r2->Divide(&p3);

    auto result_leaves = r2->ListLeafPointSet();

    std::list<IndexedPoint2dSet> answer_leaves = {
        {p3, p0, p1},
        {p3, p2, p0},
        {p3, p1, p4},
        {p3, p4, p2},
    };

    assert(EqualsAsSet(result_leaves, answer_leaves));
}