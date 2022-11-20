// Created by guinpen98

#include "../include//big_triangle_maker.h"

#include <cmath>

std::tuple<Point2d, Point2d, Point2d> MakeBigTriangle(const std::vector<IndexedPoint>& points) {
    std::pair<double, double> rect_start = {points[0]->x, points[0]->y};
    std::pair<double, double> rect_end = {points[0]->x, points[0]->y};
    for (const auto& point : points){
        if(rect_start.first > point->x){
            rect_start.first = point->x;
        }
        if(rect_start.second > point->y){
            rect_start.second = point->y;
        }
        if(rect_end.first < point->x){
            rect_end.first = point->x;
        }
        if(rect_end.second < point->y){
            rect_end.second = point->y;
        }
    }
    std::pair<double, double> center = {(rect_end.first - rect_start.first) / 2.0, (rect_end.second - rect_start.second) / 2.0};  
    double r = Vector2d{rect_end.first - center.first, rect_end.second - center.second}.Length() + 1;
    double x1 = center.first - std::sqrt(3) * r;  
    double y1 = center.second - r;
    Point2d p1 = Point2d{x1, y1};  
      
    float x2 = center.first + std::sqrt(3) * r;  
    float y2 = center.second - r;  
    Point2d p2 = Point2d{x2, y2};  
      
    float x3 = center.first;  
    float y3 = center.second + 2 * r;  
    Point2d p3 = Point2d{x3, y3}; 
    return {p1, p2, p3};
}