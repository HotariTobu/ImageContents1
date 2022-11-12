// Created by 

#include "../include/point3d.h"

Vector3d Point3d::ToVector() const {
    return Vector3d{x, y, z};
}

Point3d& Point3d::operator+=(const Point3d point) {
    x += point.x;
    y += point.y;
    z += point.z;
    return *this;
}

Point3d& Point3d::operator-=(const Point3d point) {
    x -= point.x;
    y -= point.y;
    z -= point.z;
    return *this;
}

Point3d& Point3d::operator*=(const Point3d point) {
    x *= point.x;
    y *= point.y;
    z *= point.z;
    return *this;
}

Point3d& Point3d::operator*=(const double value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

Point3d& Point3d::operator/=(const Point3d point) {
    x /= point.x;
    y /= point.y;
    z /= point.z;
    return *this;
}

Point3d& Point3d::operator/=(const double value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

bool operator==(const Point3d point1, const Point3d point2) {
    return
        point1.x == point2.x &&
        point1.y == point2.y &&
        point1.z == point2.z;
}

bool operator!=(const Point3d point1, const Point3d point2) {
    return !(point1 == point2);
}

Vector3d operator+(const Point3d point1, const Point3d point2) {
    return {
        point1.x + point2.x ,
        point1.y + point2.y ,
        point1.z + point2.z 
    };
}

Vector3d operator-(const Point3d point1, const Point3d point2) {
    return {
        point1.x - point2.x ,
        point1.y - point2.y ,
        point1.z - point2.z 
    };
}

Point3d operator*(const Point3d point, double value) {
    return {
        point.x * value ,
        point.y * value ,
        point.z * value 
    };
}

Point3d operator/(const Point3d point, double value) {
    return {
        point.x / value ,
        point.y / value ,
        point.z / value
    };
}

