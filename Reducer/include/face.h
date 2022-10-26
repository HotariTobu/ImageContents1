// Created by 

#ifndef __FACE_H__
#define __FACE_H__

#include "alias.h"
#include "point3d.h"
#include "vector3d.h"

// Represent a face consisted from multiple points.
class Face {
private:
    // A origin point of the face. 
    Point3d _origin;

    // A normal vector of the face. The length is 1.
    Vector3d _normal;


    // Points that consist the face.
    PointSet _points;

public:
    // Getter for `_points`.
    PointSet points();

    /*
    Initialize all private members.
    [params]
    - set: set of pair of points and normal vectors
    */
    Face(const PointVectorSet& set);

    /*
    Find outside points and delete the others from `_points`.
    */
    void DeleteInsidePoints();

    /*
    Project points in `_points` to the face that is defined by `_origin` and `_normal`.
    Change only Z value.
    Overwrite `_points`.
    */
    void ProjectPoints();
};


#endif // __FACE_H__