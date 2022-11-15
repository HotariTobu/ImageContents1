// Created by 

#include <cassert>

#include "../include/face.h"

bool CanPass(PointVectorSet set, Point3d origin, Vector3d normal) {
    PointSet points;
    for (std::pair<Point3d, Vector3d> pv : set) {
        points.push_back(pv.first);
    }

    Face face(set);
    return Near(face.origin(), origin) && Near(face.normal(), normal) && face.points() == points;
}

int main() {
    assert(CanPass({
        std::make_pair<Point3d, Vector3d>({ 1,  1, -1}, {0.57735 , 0.57735 , 0.57735 }),
        std::make_pair<Point3d, Vector3d>({ 1, -1,  0}, {0.408248, 0.408248, 0.816497}),
        std::make_pair<Point3d, Vector3d>({-1,  1,  0}, {0.408248, 0.816497, 0.408248}),
        std::make_pair<Point3d, Vector3d>({-1, -1,  1}, {0.816497, 0.408248, 0.408248}),
    }, {0, 0, 0}, {0.57735, 0.57735, 0.57735}));
}