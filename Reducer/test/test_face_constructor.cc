// Created by 

#include <cassert>

#include "../include/face.h"

bool Near(double a, double b) {
    return fabs(a - b) < 0.0001;
}

bool Near(Point3d, Point3d b) {
    return
        Near(a.x, b.x) &&
        Near(a.y, b.y) &&
        Near(a.z, b.z);
}

bool Near(Vector3d, Vector3d b) {
    return
        Near(a.x, b.x) &&
        Near(a.y, b.y) &&
        Near(a.z, b.z);
}

bool CanPass(PointVectorSet set, Point3d origin, Vector3d normal) {
    PointSet points(set.size());
    for (std::pair<Point3d, Vector3d> pv : set) {
        points.push_back(pv.first);
    }

    Face face(set);
    return Near(face.origin(), origin) && Near(face.normal(), normal) && face.points() == points;
}

int main() {
    assert(CanPass({
        std::make_pair({ 1,  1, -1}, {0.57735 , 0.57735 , 0.57735 }),
        std::make_pair({ 1, -1,  0}, {0.408248, 0.408248, 0.816497}),
        std::make_pair({-1,  1,  0}, {0.408248, 0.816497, 0.408248}),
        std::make_pair({-1, -1,  1}, {0.816497, 0.408248, 0.408248}),
    }, {0, 0, 0}, {0.57735, 0.57735, 0.57735}));
}