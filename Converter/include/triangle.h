// Created by 

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <set>

#include "point3d.h"
#include "circle.h"

/*
Represent a triangle.
Points are order by counter-clockwise.

Edge `points[0]` - `points[1]` is between `children[0]` and `neighbors[0]`.
Edge `points[1]` - `points[2]` is between `children[1]` and `neighbors[1]`.
Edge `points[2]` - `points[0]` is between `children[2]` and `neighbors[2]`.

`neighbors` must be assigned a pointer that is not nullptr in the end of initialization.
*/
struct Triangle {
    Point3d* points[3];

    // Child triangles inside the triangle.
    Triangle* children[3];

    // Neighbor triangles outside the triangle.
    Triangle* neighbors[3];

    /*
    Initialize all members.
    Assign `children` and `neighbors` nullptr.
    */
    Triangle(Point3d* p0, Point3d* p1, Point3d* p2);

    /*
    Delete `children`.
    */
    ~Triangle();

    /*
    Return if the triangle has any children.
    [return]
    Return false if all children is nullptr other else true.
    */
    bool HasChild() const;

    // Return the incircle.
    Circle GetIncircle();

    // Return the circumcircle.
    Circle GetCircumcircle();

    /*
    Determine whether a point is contained the triangle.
    When project the point and the point is inside the triangle on the XY plane, the triangle contains the point.
    In short, focus only X and Y values.
    [params]
    - point: a point to determine if the triangle contains it
    [return]
    If the triangle contains the point, return true, other else false.
    */
    bool Contains(Point3d* point) const;

    /*
    Find the deepest triangle containing the point.
    [params]
    - point: point that the triangle contains
    [return]
    The deepest triangle.
    */
    Triangle* FindDeepest(Point3d* point) const;

    /*
    Get index of point that consist the Triangle and a neighbor.
    The neighbor has the triangle as a neighbor identified by the index.
    [params]
    - neighbor_index: index of neighbor must be in [0, 2]
    [return]
    Return the point index.
    */
    int GetNeighborPointIndex(int neighbor_index);

    /*
    Divide the triangle into 2 or 3 triangles and add new triangles as children.
    Update `children`.
    [params]
    - point: the new vertex
    */
    void Divide(Point3d* point);

    /*
    Reconnect a edge if it is illegal.
    Check `points[1]` - `points[2]`.
    Define a point that is not in `points` and is in `points` of `neighbors[1]` as D.
    If a circumscribed circle of the triangle contains D, make new children.
    One child is consisted of `points[0]`, `points[1]`, and D.
    Another is consisted of `points[0]`, `points[2]`, and D.
    Children are assigned into both the triangle and `neighbors[1]`.
    */
    void Flip();

    /*
    Get all leaves.
    The leaf is a triangle that has no child.
    [return]
    Return list of leaves.
    */
    std::set<Triangle*> GetAllLeaves() const;
};

bool operator==(Triangle triangle1, Triangle triangle2);

bool Near(Triangle triangle1, Triangle triangle2);

#endif // __TRIANGLE_H__