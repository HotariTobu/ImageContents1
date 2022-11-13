Created by HotariTobu

#include "../include/circle.h"

bool Circle::Contains(Point3d point) const {
    Vector3d vector = center - point;
    vector.z = 0;
    double distance = vector.Length();
    return distance < radius;
}