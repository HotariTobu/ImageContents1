// Created by HotariTobu

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "point2d.h"

/*
Represent a circle on the XY plane.
*/
struct Circle {
    /*
    The center point of the circle.
    The Z value should be ignored.
    */
    Point2d center;

    // The radius of the circle.
    double radius;


    /*
    Determine whether a point is contained the circle.
    When project the point and the point is inside the circle on the XY plane, the circle contains the point.
    In short, focus only X and Y values.
    [params]
    - point: a point to determine if the circle contains it
    [return]
    If the circle contains the point, return true, other else false.
    */
    bool Contains(Point2d point) const;
};

#endif // __CIRCLE_H__