// Created by guinpen98

#include "../include//triangle.h"

bool IsSameSign(const float z1, const float z2){
    return (z1 > 0 && z2 > 0) || (z1 < 0 && z2 < 0);
}

bool Triangle::Contains(Point3d* point) const {
    Vector3d bp = *point - *points[1];
    bp.z = 0;
    Vector3d ba = *points[0] - *points[1];
    ba.z = 0;
    Vector3d bc = *points[2] - *points[1];
    bc.z = 0;
    Vector3d ca = *points[0] - *points[2];
    ca.z = 0;
    Vector3d cp = *point - *points[2];
    cp.z = 0;
    Vector3d outer_products[3] = {bp.Cross(ba), bc.Cross(bp), ca.Cross(cp)};
    return IsSameSign(outer_products[0].z, outer_products[1].z) && IsSameSign(outer_products[1].z, outer_products[2].z);
}