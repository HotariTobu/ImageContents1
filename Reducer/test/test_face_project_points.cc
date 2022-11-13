// Created by 

#include <cassert>

#include "../include/face.h"

bool CanPass(PointVectorSet set, PointSet answer) {
    Face face(set);
    face.ProjectPoints();
    
    PointSet result = face.points();
    for (int i = 0; i < result.size(); i++) {
        if (!Near(result[i], answer[i])) {
            return false;
        }
    }
    
    return true;
}

int main() {
    assert(CanPass({
        std::make_pair<Point3d, Vector3d>({ 1,  1,  0}, {0.57735 , 0.57735 , 0.57735 }),
        std::make_pair<Point3d, Vector3d>({ 1, -1, -1}, {0.408248, 0.408248, 0.816497}),
        std::make_pair<Point3d, Vector3d>({-1,  1,  1}, {0.408248, 0.816497, 0.408248}),
        std::make_pair<Point3d, Vector3d>({-1, -1,  0}, {0.816497, 0.408248, 0.408248}),
    }, {
        { 1,  1, -1},
        { 1, -1,  0},
        {-1,  1,  0},
        {-1, -1,  1},
    }));
}