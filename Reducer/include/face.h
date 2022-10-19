// Created by 

#ifndef __FACE_H__
#define __FACE_H__

#include "point_vector_set.h"

class Face {
private:
    Point3d _origin;
    Vector3d _normal;

    PointSet _points;

public:
    Face(PointVectorSet set);

    void DeleteInsidePoints();
    void ProjectPoints();
};


#endif // __FACE_H__