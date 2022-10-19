// Created by 

#ifndef __POINT_VECTOR_SET_H__
#define __POINT_VECTOR_SET_H__

#include <utility>
#include <vector>

#include "point3d.h"
#include "vector3d.h"

class PointVectorSet {
private:
    std::vector<std::pair<Point3d, Vector3d>> _data;

public:
    PointVectorSet(HeightMap map);

    std::vector<PointVectorSet> SearchPointGroups() const;
}

#endif // __POINT_VECTOR_SET_H__