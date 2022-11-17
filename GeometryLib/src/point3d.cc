// Created by baconcategg

#include "../include/point3d.h"

#include "equals.h"
#include "near.h"

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
        Equals(point1.x, point2.x) &&
        Equals(point1.y, point2.y) &&
        Equals(point1.z, point2.z);
}

bool operator!=(const Point3d point1, const Point3d point2) {
    return !(point1 == point2);
}

bool operator<(const Point3d point1, const Point3d point2) {
    double point1_values[3] = {point1.x, point1.y, point1.z};
    double point2_values[3] = {point2.x, point2.y, point2.z};
    
    for (int i = 0; i < 3; i++) {
        double difference = point1_values[i] - point2_values[i];
        if (difference < 0) {
            return true;
        }
        else if (difference > 0) {
            return false;
        }
    }
    
    return false;
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

bool Near(Point3d point1, Point3d point2) {
    return
        Near(point1.x, point2.x) &&
        Near(point1.y, point2.y) &&
        Near(point1.z, point2.z);
}
