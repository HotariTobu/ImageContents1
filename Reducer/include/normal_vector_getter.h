// Created by 

#ifndef __NORMAL_VECTOR_GETTER_H__
#define __NORMAL_VECTOR_GETTER_H__

#include "neighbor.h"
#include "vector3d.h"

/*
Calculate a normal vector of the center point.
Ignore nan in neighbors.
Finally, normalize the vector.
[params]
- neighbor: surrounding height values
[return]
The normal vector.
*/
Vector3d GetNormalVectorIn(Neighbor neighbor);

#endif // __NORMAL_VECTOR_GETTER_H__