// Created by 

#ifndef __FACE_H__
#define __FACE_H__

#include "alias.h"

struct Face {
    Point3d origin;
    Vector3d normal;

    PointSet points;
};


#endif // __FACE_H__