// Created by HotariTobu

#ifndef __GROUND_POINTS_ADDER_H__
#define __GROUND_POINTS_ADDER_H__

#include <vector>

#include "index_set.h"
#include "point2d.h"

// double ground_point_threshold;

/*
Add lower points and triangles if tilt of surround triangles is lower than a threshold.
[params]
- points: vector of the points
- indices: vector of index set of triangles
*/
void AddGroundPoints(std::vector<Point2d>& points, std::vector<double>& z_values, std::vector<IndexSet>& indices);

#endif // __GROUND_POINTS_ADDER_H__