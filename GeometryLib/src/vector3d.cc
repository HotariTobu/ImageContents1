// Created by 

#include "../include/vector3d.h"
#include<cmath>
void Vector3d::Normalize() {
    double length = Length();
    x = x / length;
    y = y / length;
    z = z / length;
}

double Vector3d::Length() const {
    return sqrt((x * x) + (y * y) + (z * z));
}

double Vector3d::Inner(const Vector3d vector) const {
    return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

Vector3d Vector3d::Cross(const Vector3d vector) const {
    return {
        (y * vector.z) - (z * vector.y) ,
        (z * vector.x) - (x * vector.z) ,
        (x * vector.y) - (y * vector.x)
    };
}

Vector3d& Vector3d::operator+=(const Vector3d vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3d& Vector3d::operator-=(const Vector3d vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Vector3d& Vector3d::operator*=(const Vector3d vector) {
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return *this;
}

Vector3d& Vector3d::operator*=(const double value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

Vector3d& Vector3d::operator/=(const Vector3d vector) {
    x /= vector.x;
    y /= vector.y;
    z /= vector.z;
    return *this;
}

Vector3d& Vector3d::operator/=(const double value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}


bool operator==(const Vector3d vector1, const Vector3d vector2) {
    return
        vector1.x == vector2.x &&
        vector1.y == vector2.y &&
        vector1.z == vector2.z;
}

bool operator!=(const Vector3d vector1, const Vector3d vector2) {
    return !(vector1 == vector2);
}

Vector3d operator+(const Vector3d vector1, const Vector3d vector2) {
    return {
        vector1.x + vector2.x ,
        vector1.y + vector2.y ,
        vector1.z + vector2.z 
    };
}

Vector3d operator-(const Vector3d vector1, const Vector3d vector2) {
    return {
        vector1.x - vector2.x ,
        vector1.y - vector2.y ,
        vector1.z - vector2.z 
    };
}

Vector3d operator*(const Vector3d vector, double value) {
    return {
        vector.x * value ,
        vector.y * value ,
        vector.z * value
    };
}

Vector3d operator/(const Vector3d vector, double value) {
    return {
        vector.x / value ,
        vector.y / value ,
        vector.z / value
    };
}