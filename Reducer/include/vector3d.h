// Created by 

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

// Represent 3D vector.
struct Vector3d {
    double x;
    double y;
    double z;
};

Vector3d operator+(const Vector3d v1, const Vector3d v2);
Vector3d operator-(const Vector3d v1, const Vector3d v2);
Vector3d operator*(const Vector3d vector, double value);
Vector3d operator/(const Vector3d vector, double value);

#endif // __VECTOR3D_H__