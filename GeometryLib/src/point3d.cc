// Created by 

#include "../include/point3d.h"

Vector3d Point3d::ToVector() const {

}

Point3d& Point3d::operator+=(const Point3d point) {

}

Point3d& Point3d::operator-=(const Point3d point) {

}

Point3d& Point3d::operator*=(const Point3d point) {

}

Point3d& Point3d::operator/=(const Point3d point) {

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

}

Vector3d operator-(const Point3d point1, const Point3d point2) {

}

Point3d operator*(const Point3d point, double value) {

}

Point3d operator/(const Point3d point, double value) {

}

