// Created by HotariTobu

#ifndef __SEARCHER_H__
#define __SEARCHER_H__

#include <map>
#include <utility>
#include <vector>

#include "alias.h"
#include "attribute.h"
#include "point2d.h"
#include "vector3d.h"

// double searcher_threshold;

/*
Create groups of points that are similar to each other for their normal vectors.
[params]
- map: map of heights and normal vector
[return]
Set of the groups of points.
*/
std::vector<PointVectorSet> SearchPointGroups(const std::map<Point2d, Attribute>& data);

#endif // __SEARCHER_H__