#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <vector>

#include "point3d.h"

/*
Represent a triangle.
Edge `point_indices[0]` - `point_indices[1]` is in between `children[0]` and `neighbors[0]`.
Edge `point_indices[1]` - `point_indices[2]` is in between `children[1]` and `neighbors[1]`.
Edge `point_indices[2]` - `point_indices[0]` is in between `children[2]` and `neighbors[2]`.
*/
struct Triangle {
    // Pointer to points.
    std::vector<Point3d>* points;

    // Indices of points that consist the triangle.
    int point_indices[3];

    // Child triangles inside the triangle.
    Triangle* children[3] = {nullptr, nullptr, nullptr};

    // Neighbor triangles outside the triangle.
    Triangle* neighbors[3] = {nullptr, nullptr, nullptr};

    bool Contains(Point3d point) const;

    void Divide(Point3d point);
};

#endif // __TRIANGLE_H__