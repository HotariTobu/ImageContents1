// Created by HotariTobu

#include "../include/face.h"

Point3d Face::origin() {
   return _origin;
}

Vector3d Face::normal() {
   return _normal;
}

std::set<std::pair<Point2d, double*>> Face::points() {
   std::set<std::pair<Point2d, double*>> result;

   for (auto [point, z] : _points) {
      result.insert({
         {
            (double)point.first,
            (double)point.second
         },
         z
      });
   }

   return result;
}