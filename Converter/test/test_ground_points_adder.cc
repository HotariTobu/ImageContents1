// Created by 

#include <cassert>
#include <set>

#include "../include/ground_points_adder.h"

extern double ground_point_threshold;

bool CanPass(PointSet points, std::vector<IndexSet> indices, std::set<std::set<Point3d, Point3d, Point3d>> triangles) {
    int mm0 = indices.size();

    AddGroundPoints(points, indices);

    int mm = indices.size();
    for (int i = mm0; i < mm; i++) {
        IndexSet index_set = indices[i];
        std::set<Point3d, Point3d, Point3d> triangle {
            points[index_set[0]],
            points[index_set[1]],
            points[index_set[2]],
        };

        auto ite = triangles.find(triangle);
        if (ite == triangles.end()) {
            return false;
        }

        triangles.erase(ite);
    }
    
    return triangles.size() == 0;
}

int main() {
    assert(CanPass(
        {
            {1, -1, 1},
            {-1, -1, 1},
            {1, 1, 1},
            {-1, 1, 1},
            {-1, -2, -1},
            {-2, -1, -1},
        },
        {
            {3, 2, 4},
            {3, 1, 2},
            {6, 5, 2},
            {5, 1, 2},
            {6, 2, 4},
        },
        {
            {
                {1, -1, 1},
                {-1, -2, -1},
                {-1, -1, -1},
            },
            {
                {-1, 1, 1},
                {-2, -1, -1},
                {-1, -1, -1},
            },
        }
    ));
}