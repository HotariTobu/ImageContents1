// Created by 

#ifndef __WRL_WRITER_H__
#define __WRL_WRITER_H__

#include <string>
#include <vector>

#include "alias.h"
#include "index_set.h"

/*
Write data to .wrl file.
Make a `IndexedFaceSet` in VRML from points and indices.
[params]
- path: path to output .wrl file
- points: set of points that consists of a polygon
- indices: set of 3 indices that consist of a triangle
*/
void WriteWRL(std::string path, const PointSet& points, const std::vector<IndexSet> indices);

#endif // __WRL_WRITER_H__