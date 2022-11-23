// Created by guinpen98

#include "../include//big_triangle_maker.h"

#include <cmath>

std::tuple<Point2d, Point2d, Point2d> MakeBigTriangle(const std::vector<IndexedPoint2d>& points) {
    Point2d rect_start = {points[0]->x, points[0]->y};
    Point2d rect_end = {points[0]->x, points[0]->y};
    for (const auto& point : points){
        if(rect_start.x > point->x){
            rect_start.x = point->x;
        }
        if(rect_start.y > point->y){
            rect_start.y = point->y;
        }
        if(rect_end.x < point->x){
            rect_end.x = point->x;
        }
        if(rect_end.y < point->y){
            rect_end.y = point->y;
        }
    }
    Point2d center = {(rect_end.x + rect_start.x) / 2.0, (rect_end.y + rect_start.y) / 2.0};  
    double r = Vector2d{rect_end.x - center.x, rect_end.y - center.y}.Length() * 1.05;

    Point2d p1 = Point2d{center.x - 2 * r, center.y - std::sqrt(3) * r};  
    Point2d p2 = Point2d{center.x + 2 * r, center.y - std::sqrt(3) * r}; 
    Point2d p3 = Point2d{center.x, center.y + 2 * r}; 

    return {p1, p2, p3};
}