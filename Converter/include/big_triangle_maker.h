// Created by HotariTobu

#ifndef __BIG_TRIANGLE_MAKER_H__
#define __BIG_TRIANGLE_MAKER_H__

#include <vector>
#include <tuple>

#include "indexed_point2d.h"

/*
Make a triangle that covers all points on XY plane.
Z values of the triangle are the mean of all Z values.
[params]
- points: vector of points
[return]
3 points that consist the triangle.
*/
std::tuple<Point2d, Point2d, Point2d> MakeBigTriangle(const std::vector<IndexedPoint2d>& points);

#endif // __BIG_TRIANGLE_MAKER_H__