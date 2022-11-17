// Created by HotariTobu

#include "../include/face.h"

 Point3d Face::origin() {
    return _origin;
 }
 
 Vector3d Face::normal() {
    return _normal;
 }
 
 PointSet Face::points() {
    return _points;
 }