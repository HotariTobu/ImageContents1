// Created by HotariTobu

#include <cassert>
#include <limits>
#include <set>

#include "../include/searcher.h"

extern double searcher_threshold;

bool CanPass(Map2d<std::pair<double, Vector3d>> map, std::set<std::set<std::pair<Point3d, Vector3d>>> answer) {
    std::vector<PointVectorSet> result = SearchPointGroups(map);

    std::set<std::set<std::pair<Point3d, Vector3d>>> result2;
    for (PointVectorSet pv : result) {
        result2.insert(std::set(pv.begin(), pv.end()));
    }

    return result2 == answer;
}

std::pair<double, Vector3d> pack(double value, Vector3d vector) {
    return std::make_pair(value, vector);
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    searcher_threshold = 0.5;

    assert(CanPass({
        0, 0, 4, 4,
        {
            {pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan})},
            {pack(nan, {nan, nan, nan}), pack(  1, {0.1, 0.0, 0.9}), pack(  2, {0.0, 1.0, 0.0}), pack(  3, {0.0, 0.9, 0.1}), pack(  4, {0.1, 1.0, 0.0}), pack(nan, {nan, nan, nan})},
            {pack(nan, {nan, nan, nan}), pack(  5, {0.0, 0.0, 1.0}), pack(  6, {0.0, 0.0, 1.0}), pack(  7, {0.1, 0.0, 1.0}), pack(  8, {0.0, 1.0, 0.0}), pack(nan, {nan, nan, nan})},
            {pack(nan, {nan, nan, nan}), pack(  9, {0.0, 0.1, 0.9}), pack( 10, {0.0, 0.1, 1.0}), pack( 11, {0.0, 1.0, 0.0}), pack( 12, {0.0, 1.0, 0.1}), pack(nan, {nan, nan, nan})},
            {pack(nan, {nan, nan, nan}), pack( 13, {0.0, 0.0, 1.0}), pack( 14, {0.1, 0.9, 0.0}), pack( 15, {0.0, 1.0, 0.0}), pack( 16, {0.1, 0.9, 0.0}), pack(nan, {nan, nan, nan})},
            {pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan}), pack(nan, {nan, nan, nan})},
        }
    }, {
        {
            std::make_pair<Point3d, Vector3d>({0, 0,  1}, {0.1, 0.0, 0.9}),
            std::make_pair<Point3d, Vector3d>({0, 1,  5}, {0.0, 0.0, 1.0}),
            std::make_pair<Point3d, Vector3d>({0, 2,  9}, {0.0, 0.1, 0.9}),
            std::make_pair<Point3d, Vector3d>({0, 3, 13}, {0.0, 0.0, 1.0}),
            std::make_pair<Point3d, Vector3d>({1, 1,  6}, {0.0, 0.0, 1.0}),
            std::make_pair<Point3d, Vector3d>({1, 2, 10}, {0.0, 0.1, 1.0}),
            std::make_pair<Point3d, Vector3d>({2, 1,  7}, {0.1, 0.0, 1.0}),
        },
        {
            std::make_pair<Point3d, Vector3d>({1, 0,  2}, {0.0, 1.0, 0.0}),
            std::make_pair<Point3d, Vector3d>({1, 3, 14}, {0.1, 0.9, 0.0}),
            std::make_pair<Point3d, Vector3d>({2, 0,  3}, {0.0, 0.9, 0.1}),
            std::make_pair<Point3d, Vector3d>({2, 2, 11}, {0.0, 1.0, 0.0}),
            std::make_pair<Point3d, Vector3d>({2, 3, 15}, {0.0, 1.0, 0.0}),
            std::make_pair<Point3d, Vector3d>({3, 0,  4}, {0.1, 1.0, 0.0}),
            std::make_pair<Point3d, Vector3d>({3, 1,  8}, {0.0, 1.0, 0.0}),
            std::make_pair<Point3d, Vector3d>({3, 2, 12}, {0.0, 1.0, 0.1}),
            std::make_pair<Point3d, Vector3d>({3, 3, 16}, {0.1, 0.9, 0.0}),
        },
    }));
}