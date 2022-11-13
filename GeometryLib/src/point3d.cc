// Created by 

#include "../include/point3d.h"

#include "equals.h"
#include "near.h"

Vector3d Point3d::ToVector() const {

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

}

Vector3d operator-(const Point3d point1, const Point3d point2) {

}

Point3d operator*(const Point3d point, double value) {

}

Point3d operator/(const Point3d point, double value) {

}

bool Near(Point3d point1, Point3d point2) {
    return
        Near(point1.x, point2.x) &&
        Near(point1.y, point2.y) &&
        Near(point1.z, point2.z);
}
