// Created by 

#ifndef __BIG_TRIANGLE_MAKER_H__
#define __BIG_TRIANGLE_MAKER_H__

#include <utility>

#include "point3d.h"
#include "alias.h"

/*
Make a triangle that covers all points on XY plane.
Z values of the triangle are the mean of all Z values.
[params]
- points: set of points
[return]
3 points that consist the triangle.
*/
std::tuple<Point3d, Point3d, Point3d> MakeBigTriangle(const PointSet& points);

#endif // __BIG_TRIANGLE_MAKER_H__