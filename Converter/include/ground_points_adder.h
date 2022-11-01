// Created by 

#ifndef __GROUND_POINTS_ADDER_H__
#define __GROUND_POINTS_ADDER_H__

#include <vector>

#include "alias.h"
#include "index_set.h"

/*
Add lower points and triangles if tilt of surround triangles is bigger than a threshold.
*/
void AddGroundPoints(PointSet& points, std::vector<IndexSet> indices);

#endif // __GROUND_POINTS_ADDER_H__