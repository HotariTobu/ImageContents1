// Created by HotariTobu

#ifndef __WRL_WRITER_H__
#define __WRL_WRITER_H__

#include <list>
#include <map>
#include <string>

#include "point2d.h"
#include "attribute.h"
#include "index_set.h"
#include "indexed_point2d.h"

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
void WriteWRL(const std::string& path, const std::map<Point2d, Attribute>& data, const std::list<IndexedPoint2dSet>& point_set_list, const std::list<std::pair<Point2d, double>>& additional_points = {}, const std::list<IndexSet>& additional_index_set_list = {});

#endif // __WRL_WRITER_H__