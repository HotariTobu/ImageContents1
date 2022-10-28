// Created by 

#ifndef __GROUND_POINTS_MAKER_H__
#define __GROUND_POINTS_MAKER_H__

#include "map2d"

/*
Make points that are below given points.
If value is nan, return value is nan, too.
Fill non nan points with a height value.
The height value is min of values if it is smaller than 0, other else 0.
*/
Map2d<double> MakeGroundPoints(const Map2d<double>& map);

#endif // __GROUND_POINTS_MAKER_H__