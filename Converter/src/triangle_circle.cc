// Created by guinpen98

#include "../include/triangle.h"

#include <cmath>

double HeronsFormula(const double a, const double b, const double c){
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double CalculateCos(const Vector3d& a, const Vector3d& b){
    return a.Inner(b) / a.Length() / b.Length();

}

double CosToSin(const double cos){
    return std::sqrt(1 - cos * cos);
}

Circle Triangle::GetIncircle() {
    double d1 = (*points[1] - *points[2]).Length();
    double d2 = (*points[2] - *points[0]).Length();
    double d3 = (*points[0] - *points[1]).Length();
    double d123 = d1 + d2 + d3;

    Point3d center;
    center.x = (d1 * points[0]->x + d2 * points[1]->x + d3 * points[2]->x) / d123;
    center.y = (d1 * points[0]->y + d2 * points[1]->y + d3 * points[2]->y) / d123;
    center.z = (d1 * points[0]->z + d2 * points[1]->z + d3 * points[2]->z) / d123;
    double r = (2 * HeronsFormula(d1, d2, d3)) / (d123);
    return Circle{center, r};
}

Circle Triangle::GetCircumcircle() {
    double a = (*points[1] - *points[2]).Length();
    double b = (*points[2] - *points[0]).Length();
    double c = (*points[0] - *points[1]).Length();
    
    Vector3d v_a = points[0]->ToVector();
    Vector3d v_b = points[1]->ToVector();
    Vector3d v_c = points[2]->ToVector();

    double cos_a = CalculateCos(*points[1] - *points[0], *points[2] - *points[0]);
    double cos_b = CalculateCos(*points[0] - *points[1], *points[2] - *points[1]);
    double cos_c = CalculateCos(*points[0] - *points[2], *points[1] - *points[2]);

    double sin_a = CosToSin(cos_a);
    double sin_b = CosToSin(cos_b);
    double sin_c = CosToSin(cos_c);

    double sin_2a = 2 * sin_a * cos_a;
    double sin_2b = 2 * sin_b * cos_b;
    double sin_2c = 2 * sin_c * cos_c;

    double r = a / 2 / sin_a;
    Point3d center = ((v_a * sin_2a + v_b * sin_2b + v_c * sin_2c) / (sin_2a + sin_2b + sin_2c)).ToPoint();
    return Circle{center, r};
}