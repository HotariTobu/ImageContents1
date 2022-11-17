// Created by HotariTobu

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

struct Point3d;

// Represent 3D vector.
struct Vector3d {
    double x;
    double y;
    double z;

    // Make the length 1.
    void Normalize();


    // Return the length.
    double Length() const;

    // Calculate inner product with `vector`.
    double Inner(const Vector3d vector) const;

    // Calculate cross product with `vector`.
    Vector3d Cross(const Vector3d vector) const;
    
    // Return the vector as a point.
    Point3d ToPoint() const;

    Vector3d& operator+=(const Vector3d vector);
    Vector3d& operator-=(const Vector3d vector);
    Vector3d& operator*=(const Vector3d vector);
    Vector3d& operator*=(const double value);
    Vector3d& operator/=(const Vector3d vector);
    Vector3d& operator/=(const double value);
};

bool operator==(const Vector3d vector1, const Vector3d vector2);
bool operator!=(const Vector3d vector1, const Vector3d vector2);

bool operator<(const Vector3d vector1, const Vector3d vector2);

Vector3d operator+(const Vector3d vector1, const Vector3d vector2);
Vector3d operator-(const Vector3d vector1, const Vector3d vector2);
Vector3d operator*(const Vector3d vector, double value);
Vector3d operator/(const Vector3d vector, double value);

bool Near(Vector3d vector1, Vector3d vector2);

#endif // __VECTOR3D_H__