// Created by HotariTobu

#ifndef __POINT2D_H__
#define __POINT2D_H__

#include "vector2d.h"

// Represent 2d point.
struct Point2d {
    double x;
    double y;
    

    // Return the point as a vector.
    Vector2d ToVector() const;

    Point2d& operator+=(const Point2d point);
    Point2d& operator-=(const Point2d point);
    Point2d& operator*=(const Point2d point);
    Point2d& operator*=(const double value);
    Point2d& operator/=(const Point2d point);
    Point2d& operator/=(const double value);
};

bool operator==(const Point2d point1, const Point2d point2);
bool operator!=(const Point2d point1, const Point2d point2);

bool operator<(const Point2d point1, const Point2d point2);

Vector2d operator+(const Point2d point1, const Point2d point2);
Vector2d operator-(const Point2d point1, const Point2d point2);
Point2d operator*(const Point2d point, double value);
Point2d operator/(const Point2d point, double value);

bool Near(Point2d point1, Point2d point2);

#endif // __POINT2D_H__