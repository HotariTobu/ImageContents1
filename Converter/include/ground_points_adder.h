// Created by HotariTobu

#ifndef __GROUND_POINTS_ADDER_H__
#define __GROUND_POINTS_ADDER_H__

#include <list>
#include <map>

#include "point2d.h"
#include "point3d.h"
#include "attribute.h"
#include "indexed_point.h"

// double ground_point_threshold;

/*
Add lower points and triangles if tilt of surround triangles is lower than a threshold.
[params]
- points: vector of the points
- indices: vector of index set of triangles
*/
std::list<Point3d> AddGroundPoints(const std::map<Point2d, Attribute>& data, const std::list<IndexedPointSet>& point_set_list);

#endif // __GROUND_POINTS_ADDER_H__