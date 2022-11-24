// Created by HotariTobu

#ifndef __FACE_H__
#define __FACE_H__

#include <list>

#include "point2d.h"
#include "vector3d.h"

// Represent a face consisted from multiple points.
class Face {
private:
    // A origin point of the face. 
    Point3d _origin;

    // A normal vector of the face. The length is 1.
    Vector3d _normal;


    // Points that consist the face.
    std::list<std::pair<Point2d, double*>> _points;

public:
    // Getter for `_origin`.
    Point3d origin();

    // Getter for `_normal`.
    Vector3d normal();
    

    // Getter for `_points`.
    std::list<std::pair<Point2d, double*>> points();

    /*
    Initialize all private members.
    [params]
    - set: set of pair of points and normal vectors
    */
    Face(const std::list<std::pair<std::pair<Point2d, double*>, const Vector3d*>>& point_vector_list);

    /*
    Find outside points and delete the others from `_points`.
    */
    std::list<Point2d> DeleteInsidePoints();

    /*
    Project points in `_points` to the face that is defined by `_origin` and `_normal`.
    Change only Z value.
    Overwrite `_points`.
    */
    void ProjectPoints();
};


#endif // __FACE_H__