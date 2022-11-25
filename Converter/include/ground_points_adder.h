// Created by HotariTobu

#ifndef __GROUND_POINTS_ADDER_H__
#define __GROUND_POINTS_ADDER_H__

#include <list>
#include <map>

#include "point2d.h"
#include "attribute.h"
#include "index_set.h"
#include "indexed_point2d.h"

// double ground_point_threshold;

/*
Add lower points and triangles if tilt of surround triangles is lower than a threshold.
[params]
- points: vector of the points
- indices: vector of index set of triangles
*/
std::pair<std::list<std::pair<Point2d, double>>, std::list<IndexSet>> AddGroundPoints(const std::map<Point2d, Attribute>& data, std::list<IndexedPoint2dSet>& point_set_list);

#endif // __GROUND_POINTS_ADDER_H__