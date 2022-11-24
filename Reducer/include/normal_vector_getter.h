// Created by HotariTobu

#ifndef __NORMAL_VECTOR_GETTER_H__
#define __NORMAL_VECTOR_GETTER_H__

#include "neighbor.h"
#include "vector3d.h"
#include "reducer_attribute.h"

/*
Calculate a normal vector of the center point.
Ignore nan in neighbors.
Finally, normalize the vector.
[params]
- neighbor: surrounding height values
[return]
The normal vector.
*/
Vector3d GetNormalVectorIn(Neighbor<ReducerAttribute> neighbor);

#endif // __NORMAL_VECTOR_GETTER_H__