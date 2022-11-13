// Created by 

#ifndef __MAPS_COMBINER_H__
#define __MAPS_COMBINER_H__

#include <vector>

#include "map2d.h"

/*
Combine multiple maps into a map.
Use a value of the last map if there are multiple values in a point.
[params]
- maps: set of map
[return]
Return combined map.
*/
Map2d<double> CombineMaps(const std::vector<Map2d<double>>& maps);

#endif // __MAPS_COMBINER_H__