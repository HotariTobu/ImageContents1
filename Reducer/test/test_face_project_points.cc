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
    assert({
        std::make_pair({ 1,  1,  0}, {0.57735 , 0.57735 , 0.57735 }),
        std::make_pair({ 1, -1, -1}, {0.408248, 0.408248, 0.816497}),
        std::make_pair({-1,  1,  1}, {0.408248, 0.816497, 0.408248}),
        std::make_pair({-1, -1,  0}, {0.816497, 0.408248, 0.408248}),
    }, {
        { 1,  1, -1}
        { 1, -1,  0}
        {-1,  1,  0}
        {-1, -1,  1}
    });
}