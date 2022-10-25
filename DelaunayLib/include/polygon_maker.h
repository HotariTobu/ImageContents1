// Created by 

#ifndef __POLYGON_MAKER_H__
#define __POLYGON_MAKER_H__

#include <utility>
#include <vector>

#include "point3d.h"

/*
Make a polygon from point set.
[params]
- points: set of points
[return]
Point indices of triangle based on `points`.
*/
std::vector<std::tuple<int, int, int>> MakePolygon(const std::vector<Point3d>& points);

#endif // __POLYGON_MAKER_H__