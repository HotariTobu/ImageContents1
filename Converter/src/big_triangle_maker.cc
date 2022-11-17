// Created by guinpen98

#include "../include//big_triangle_maker.h"

#include <cmath>
#include <tuple>

std::tuple<Point3d, Point3d, Point3d> MakeBigTriangle(const PointSet& points) {
    std::pair<double, double> rect_start = {points[0].x, points[0].y};
    std::pair<double, double> rect_end = {points[0].x, points[0].y};
    double sum_z = 0;
    for (const auto& point : points){
        if(rect_start.first > point.x){
            rect_start.first = point.x;
        }
        if(rect_start.second > point.y){
            rect_start.second = point.y;
        }
        if(rect_end.first < point.x){
            rect_end.first = point.x;
        }
        if(rect_end.second < point.y){
            rect_end.second = point.y;
        }
        sum_z += point.z;
    }
    std::pair<double, double> center = {(rect_end.first - rect_start.first) / 2.0, (rect_end.second - rect_start.second) / 2.0};  
    double r = Vector3d{rect_end.first - center.first, rect_end.second - center.second, 0}.Length() + 1;
    double x1 = center.first - std::sqrt(3) * r;  
    double y1 = center.second - r;  
    double z = sum_z / points.size();
    Point3d p1 = Point3d{x1, y1, z};  
      
    float x2 = center.first + std::sqrt(3) * r;  
    float y2 = center.second - r;  
    Point3d p2 = Point3d{x2, y2, z};  
      
    float x3 = center.first;  
    float y3 = center.second + 2 * r;  
    Point3d p3 = Point3d{x3, y3, z}; 
    return std::make_tuple(p1, p2, p3);
}