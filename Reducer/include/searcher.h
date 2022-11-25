// Created by HotariTobu

#ifndef __SEARCHER_H__
#define __SEARCHER_H__

#include <list>

#include "reducer_attribute.h"
#include "z_map.h"

// double searcher_threshold;

/*
Create groups of points that are similar to each other for their normal vectors.
A group includes a point if the inner product of normal vectors of the point and a neighbor point in the group is bigger than the threshold. 
[params]
- z_map: a map that the key is a 2d point and the value is the attribute of the point that includes the normal vector
[return]
List of indices lists to reference `ZMap::z_values`.
An indices list consists of indices of points that are in the same group.
*/
std::list<std::list<int>> SearchPointGroups(const ZMap<ReducerAttribute>& z_map);

#endif // __SEARCHER_H__