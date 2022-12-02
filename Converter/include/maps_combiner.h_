// Created by HotariTobu

#ifndef __MAPS_COMBINER_H__
#define __MAPS_COMBINER_H__

#include <list>

#include "map2d.h"
#include "point_type.h"

/*
Combine multiple maps into a map.
Use a value of the last map if there are multiple values in a point.
[params]
- maps: list of map and type of the map
[return]
Return combined map.
An element had height and type.
*/
Map2d<std::pair<double, PointType>> CombineMaps(const std::list<std::pair<Map2d<double>, PointType>>& maps);

#endif // __MAPS_COMBINER_H__