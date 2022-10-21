// Created by 

#ifndef __SEPARATOR_H__
#define __SEPARATOR_H__

#include <utility>

#include "map2d.h"

// double separator_threshold;

/*
Separate map to ground map and building map.
If ease of stay is bigger than `separator_threshold`, the point is on ground, and other else on building.
[params]
- map: map of heights
- ease_of_stay: map of ease of stay values
[return]
- 1st Map2d: ground map
- 2nd Map2d: building map
Fill points that do not consist map with nan of double.
*/
std::pair<Map2d, Map2d> Separate(Map2d map, Map2d ease_of_stay);

#endif // __SEPARATOR_H__