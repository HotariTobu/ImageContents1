// Created by 

#ifndef __POINT3D_H__
#define __POINT3D_H__

#include "vector3d.h"

// Represent 3D point.
struct Point3d {
    double x;
    double y;
    double z;

    // Return the point as a vector.
    Vector3d ToVector() const;
};

bool operator==(const Point3d point1, const Point3d point2);
bool operator!=(const Point3d point1, const Point3d point2);

bool operator<(const Point3d point1, const Point3d point2);

Vector3d operator+(const Point3d point1, const Point3d point2);
Vector3d operator-(const Point3d point1, const Point3d point2);
Point3d operator*(const Point3d point, double value);
Point3d operator/(const Point3d point, double value);

bool Near(Point3d point1, Point3d point2);

#endif // __POINT3D_H__