// Created by guinpen98

#include "../include/triangle.h"

#include <cmath>

double HeronsFormula(const double a, const double b, const double c){
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double CalculateCos(Vector3d a, Vector3d b){
    a.z = 0;
    b.z = 0;
    return a.Inner(b) / a.Length() / b.Length();

}

double CosToSin(const double cos){
    return std::sqrt(1 - cos * cos);
}

Circle Triangle::GetIncircle() {
    Vector3d v_a = *points[1] - *points[2];
    Vector3d v_b = *points[2] - *points[0];
    Vector3d v_c = *points[0] - *points[1];

    v_a.z = 0;
    v_b.z = 0;
    v_c.z = 0;

    double d1 = v_a.Length();
    double d2 = v_b.Length();
    double d3 = v_c.Length();
    double d123 = d1 + d2 + d3;

    Point3d center;
    center.x = (d1 * points[0]->x + d2 * points[1]->x + d3 * points[2]->x) / d123;
    center.y = (d1 * points[0]->y + d2 * points[1]->y + d3 * points[2]->y) / d123;
    center.z = 0;
    double r = (2 * HeronsFormula(d1, d2, d3)) / (d123);
    return Circle{center, r};
}

Circle Triangle::GetCircumcircle() {
    Vector3d v_bc = *points[1] - *points[2];
    Vector3d v_ca = *points[2] - *points[0];
    Vector3d v_ab = *points[0] - *points[1];

    v_bc.z = 0;
    v_ca.z = 0;
    v_ab.z = 0;

    double a = v_bc.Length();
    double b = v_ca.Length();
    double c = v_ab.Length();
    
    Vector3d v_a = points[0]->ToVector();
    Vector3d v_b = points[1]->ToVector();
    Vector3d v_c = points[2]->ToVector();
    
    v_a.z = 0;
    v_b.z = 0;
    v_c.z = 0;

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