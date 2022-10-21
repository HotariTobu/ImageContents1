// Created by 

#ifndef __POINT_VECTOR_SET_H__
#define __POINT_VECTOR_SET_H__

#include <utility>
#include <vector>

#include "point3d.h"
#include "vector3d.h"

// Represent set of pair of points and normal vectors.
class PointVectorSet {
private:
    // Set of pair of points and normal vectors.
    std::vector<std::pair<Point3d, Vector3d>> _data;

    /*
    Calculate normal a vector of a point.
    [params]
    - point: a point
    [return]
    The 
    */
    static Vector3d GetNormalVectorOf(Point3d point);

public:
    /*
    Calculate normal vectors of each points
    */
    PointVectorSet(Map2d map);

    std::vector<PointVectorSet> SearchPointGroups() const;
}

#endif // __POINT_VECTOR_SET_H__