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


    /*
    Determine whether a point is inside the triangle.
    [params]
    - point: a point to determine if the triangle contains it
    [return]
    If the triangle contains the point, return true, other else false.
    */
    bool Contains(Point3d point) const;

    /*
    Divide the triangle into 2 or 3 triangles.
    Find the deepest triangle containing the point and add new triangles as children.
    [params]
    - point: the new vertex
    */
    void Divide(Point3d point);

    /*
    Reconnect a edge if it is illegal.
    Check `point_indices[1]` - `point_indices[2]`.
    Define a point that is not in `point_indices` and is in `point_indices` of `neighbors[1]` as D.
    If a circumscribed circle of the triangle contains D, make new children.
    One child is consisted of `point_indices[0]`, `point_indices[1]`, and D.
    Another is consisted of `point_indices[0]`, `point_indices[2]`, and D.
    Children are assigned into both the triangle and `neighbors[1]`.
    */
    void Flip();
};

#endif // __TRIANGLE_H__