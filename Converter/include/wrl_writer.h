// Created by HotariTobu

#ifndef __WRL_WRITER_H__
#define __WRL_WRITER_H__

#include <string>
#include <vector>

#include "alias.h"
#include "map2d.h"
#include "index_set.h"
#include "point_type.h"

/*
Write data to .wrl file.
Make a `IndexedFaceSet` in VRML from points and indices.
Ground point's color is #00FF00, building point's is #FF0000, and other's is #FFFFFF.
[params]
- path: path to output .wrl file
- points: set of points that consists of a polygon
- indices: set of 3 indices that consist of a triangle
- point_types: map of `PointType` that whether a point is on ground or on building
*/
void WriteWRL(std::string path, const PointSet& points, const std::vector<IndexSet>& indices, const Map2d<PointType>& point_types);

#endif // __WRL_WRITER_H__