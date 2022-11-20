// Created by HotariTobu

#ifndef __ROOT_MAKER_H__
#define __ROOT_MAKER_H__

#include "triangle.h"

/*
Make a root triangle.
The triangle is set with a dummy triangle.
They are neighbors of each other.
The root's points are ordered counter-clockwise but the dummy is clockwise.
[param]
points to initialize the triangles
[return]
- 1st triangle: the root
- 2nd triangle: the dummy
*/
std::pair<std::shared_ptr<Triangle>, std::shared_ptr<Triangle>> MakeRoot(const IndexedPoint& p0, const IndexedPoint& p1, const IndexedPoint& p2);


#endif // __ROOT_MAKER_H__