// Created by 

#ifndef __FACE_H__
#define __FACE_H__

#include "point_vector_set.h"

// Represent a face consisted from multiple points.
class Face {
private:
    // A origin point of the face. 
    Point3d _origin;

    // A normal vector of the face.
    Vector3d _normal;


    // Points that consist the face.
    PointSet _points;

public:
    /*
    Initialize all private members.
    [params]
    - set: set of pair of points and normal vectors
    */
    Face(PointVectorSet set);

    /*
    Find outside points and delete the others from `_points`.
    */
    void DeleteInsidePoints();

    /*
    Project points in `_points` to the face that is defined by `_origin` and `_normal`.
    Overwrite `_points`.
    */
    void ProjectPoints();
};


#endif // __FACE_H__