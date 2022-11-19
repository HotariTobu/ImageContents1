// Created by HotariTobu

#include "../include/circle.h"

bool Circle::Contains(Point2d point) const {
    Vector2d vector = center - point;
    double distance = vector.Length();
    return distance < radius;
}