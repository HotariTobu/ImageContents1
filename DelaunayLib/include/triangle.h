#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "point3d.h"

struct Triangle {
    Point3d points[3];
    Triangle* children[3] = {nullptr, nullptr, nullptr};
    Triangle* neighbors[3] = {nullptr, nullptr, nullptr};
}

#endif // __TRIANGLE_H__