// Created by baconcategg

#include "../include/point2d.h"

#include "equals.h"
#include "near.h"

Vector2d Point2d::ToVector() const {
    return Vector2d{x, y};
}

Point2d& Point2d::operator+=(const Point2d point) {
    x += point.x;
    y += point.y;
    return *this;
}

Point2d& Point2d::operator-=(const Point2d point) {
    x -= point.x;
    y -= point.y;
    return *this;
}

Point2d& Point2d::operator*=(const Point2d point) {
    x *= point.x;
    y *= point.y;
    return *this;
}

Point2d& Point2d::operator/=(const Point2d point) {
    x /= point.x;
    y /= point.y;
    return *this;
}

Point2d& Point2d::operator*=(const double value) {
    x *= value;
    y *= value;
    return *this;
}

Point2d& Point2d::operator/=(const double value) {
    x /= value;
    y /= value;
    return *this;
}

bool operator==(const Point2d point1, const Point2d point2) {
    return
        Equals(point1.x, point2.x) &&
        Equals(point1.y, point2.y);
}

bool operator!=(const Point2d point1, const Point2d point2) {
    return !(point1 == point2);
}

bool operator<(const Point2d point1, const Point2d point2) {
    double point1_values[2] = {point1.x, point1.y};
    double point2_values[2] = {point2.x, point2.y};
    
    for (int i = 0; i < 2; i++) {
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

Point2d operator+(const Point2d point1, const Point2d point2) {
    return {
        point1.x + point2.x ,
        point1.y + point2.y
    };
}

Vector2d operator-(const Point2d point1, const Point2d point2) {
    return {
        point1.x - point2.x ,
        point1.y - point2.y
    };
}

Point2d operator*(const Point2d point, double value) {
    return {
        point.x * value ,
        point.y * value
    };
}

Point2d operator/(const Point2d point, double value) {
    return {
        point.x / value ,
        point.y / value
    };
}

bool Near(Point2d point1, Point2d point2) {
    return
        Near(point1.x, point2.x) &&
        Near(point1.y, point2.y);
}
