// Created by 

#include "../include/ground_points_adder.h"

#include <forward_list>

struct Context {
    std::forward_list<IndexSet> index_set_list;
    double tilt;
    Point3d origin;
};


double GetTilt(Point3d p1, Point3d p2, Point3d p3) {

}

Point3d GetOrigin(Point3d p1, Point3d p2, Point3d p3) {
    
}

void AddGroundPoints(PointSet& points, std::vector<IndexSet> indices) {
    int n = points.size();
    Context contexts[n];
}