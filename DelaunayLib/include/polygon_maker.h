// Created by 

#ifndef __POLYGON_MAKER_H__
#define __POLYGON_MAKER_H__

#include <utility>
#include <vector>

#include "alias.h"
#include "point3d.h"

/*
Make a polygon of points with delaunay triangulation.
[params]
- points: set of points
[return]
Point indices of triangle based on `points`.
*/
std::vector<std::tuple<int, int, int>> MakePolygon(const PointSet& points);

#endif // __POLYGON_MAKER_H__