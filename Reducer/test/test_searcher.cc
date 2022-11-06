// Created by 

#include <cassert>
#include <set>

#include "../include/searcher.h"

using namespace std;

extern double searcher_threshold;

bool CanPass(Map2d<pair<double, Vector3d>> map, set<set<pair<Point3d, Vector3d>>> answer) {
    vector<PointVectorSet> result = SearchPointGroups(map);

    set<set<pair<Point3d, Vector3d>>> result2;
    for (PointVectorSet pv : result) {
        result2.insert(set(pv.begin(), pv.end()));
    }

    return result2 == answer;
}

int main() {
    constexpr double nan = numeric_limits<double>::quiet_NaN();

    searcher_threshold = 0.5;

    assert(CanPass({
        0, 0, 4, 4,
        {
            {make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan})},
            {make_pair(nan, {nan, nan, nan}), make_pair(  1, {0.1, 0.0, 0.9}), make_pair(  2, {0.0, 1.0, 0.0}), make_pair(  3, {0.0, 0.9, 0.1}), make_pair(  4, {0.1, 1.0, 0.0}), make_pair(nan, {nan, nan, nan})},
            {make_pair(nan, {nan, nan, nan}), make_pair(  5, {0.0, 0.0, 1.0}), make_pair(  6, {0.0, 0.0, 1.0}), make_pair(  7, {0.1, 0.0, 1.0}), make_pair(  8, {0.0, 1.0, 0.0}), make_pair(nan, {nan, nan, nan})},
            {make_pair(nan, {nan, nan, nan}), make_pair(  9, {0.0, 0.1, 0.9}), make_pair( 10, {0.0, 0.1, 1.0}), make_pair( 11, {0.0, 1.0, 0.0}), make_pair( 12, {0.0, 1.0, 0.1}), make_pair(nan, {nan, nan, nan})},
            {make_pair(nan, {nan, nan, nan}), make_pair( 13, {0.0, 0.0, 1.0}), make_pair( 14, {0.1, 0.9, 0.0}), make_pair( 15, {0.0, 1.0, 0.0}), make_pair( 16, {0.1, 0.9, 0.0}), make_pair(nan, {nan, nan, nan})},
            {make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan}), make_pair(nan, {nan, nan, nan})},
        }
    }, {
        {
            make_pair({0, 0,  1}, {0.1, 0.0, 0.9}),
            make_pair({0, 1,  5}, {0.0, 0.0, 1.0}),
            make_pair({0, 2,  9}, {0.0, 0.1, 0.9}),
            make_pair({0, 3, 13}, {0.0, 0.0, 1.0}),
            make_pair({1, 1,  6}, {0.0, 0.0, 1.0}),
            make_pair({1, 2, 10}, {0.0, 0.1, 1.0}),
            make_pair({2, 1,  7}, {0.1, 0.0, 1.0}),
        },
        {
            make_pair({1, 0,  2}, {0.0, 1.0, 0.0}),
            make_pair({1, 3, 14}, {0.1, 0.9, 0.0}),
            make_pair({2, 0,  3}, {0.0, 0.9, 0.1}),
            make_pair({2, 2, 11}, {0.0, 1.0, 0.0}),
            make_pair({2, 3, 15}, {0.0, 1.0, 0.0}),
            make_pair({3, 0,  4}, {0.1, 1.0, 0.0}),
            make_pair({3, 1,  8}, {0.0, 1.0, 0.0}),
            make_pair({3, 2, 12}, {0.0, 1.0, 0.1}),
            make_pair({3, 3, 16}, {0.1, 0.9, 0.0}),
        },
    }));
}