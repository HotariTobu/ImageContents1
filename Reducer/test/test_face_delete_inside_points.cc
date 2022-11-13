// Created by 

#include <cassert>

#include "../include/face.h"

bool CanPass(PointVectorSet set, PointSet answer) {
    Face face(set);
    face.DeleteInsidePoints();
    return face.points() == answer;
}

int main() {
    assert(CanPass({
        std::make_pair<Point3d, Vector3d>({ 1,  1, 0}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({-1,  1, 0}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({ 1, -1, 0}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({-1, -1, 0}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.1, 0.2, 0.3}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.2, 0.3, 0.4}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.3, 0.4, 0.5}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.4, 0.5, 0.6}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.5, 0.6, 0.7}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.6, 0.7, 0.8}, {0, 0, 0}),
        std::make_pair<Point3d, Vector3d>({0.7, 0.8, 0.9}, {0, 0, 0}),
    }, {
        { 1,  1, 0},
        {-1,  1, 0},
        { 1, -1, 0},
        {-1, -1, 0},
    }));
}