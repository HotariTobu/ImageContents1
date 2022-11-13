// Created by 

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "point3d.h"

struct Circle {
    Point3d center;
    double radius;

    bool Contains(Point3d point) const;
};

#endif // __CIRCLE_H__