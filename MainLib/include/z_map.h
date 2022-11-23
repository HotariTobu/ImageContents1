// Created by HotariTobu

#ifndef __Z_MAP_H__
#define __Z_MAP_H__

#include <list>
#include <map>
#include <memory>

#include "point2d.h"
#include "rectangle.h"

struct ZMap {
    Rectangle rectangle;
    
    int width;
    int height;

    int stride;

    std::unique_ptr<const double*[]> z_values;
    std::list<int> nan_point_indices;

    ZMap(const std::map<Point2d, double>& data, const Rectangle& rectangle);
    Point2d GetPoint(int index) const;
};

#endif // __Z_MAP_H__