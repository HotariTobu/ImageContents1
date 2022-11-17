// Created by HotariTobu

#ifndef __SEARCHER_H__
#define __SEARCHER_H__

#include <utility>
#include <vector>

#include "map2d.h"
#include "alias.h"
#include "vector3d.h"

// double searcher_threshold;

/*
Create groups of points that are similar to each other for their normal vectors.
[params]
- map: map of heights and normal vector
[return]
Set of the groups of points.
*/
std::vector<PointVectorSet> SearchPointGroups(const Map2d<std::pair<double, Vector3d>>& map);

#endif // __SEARCHER_H__