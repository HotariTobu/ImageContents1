// Created by 

#ifndef __POINT3D_H__
#define __POINT3D_H__

// Represent 3D point.
struct Point3d {
    double x;
    double y;
    double z;
};

Point3d operator+(const Point3d p1, const Point3d p2);
Point3d operator-(const Point3d p1, const Point3d p2);
Point3d operator*(const Point3d point, double value);
Point3d operator/(const Point3d point, double value);

#endif // __POINT3D_H__