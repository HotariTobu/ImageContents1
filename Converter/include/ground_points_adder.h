// Created by 

#ifndef __GROUND_POINTS_ADDER_H__
#define __GROUND_POINTS_ADDER_H__

#include "alias.h"
#include "index_set.h"

// double ground_point_threshold;

/*
Add lower points and triangles if tilt of surround triangles is lower than a threshold.
*/
void AddGroundPoints(PointSet& points, std::vector<IndexSet>& indices);

#endif // __GROUND_POINTS_ADDER_H__