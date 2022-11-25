// Created by HotariTobu

#ifndef __Z_MAP_H__
#define __Z_MAP_H__

#include <list>
#include <map>
#include <memory>

#include "point2d.h"
#include "rectangle.h"

template<typename T>
struct ZMap {
    Rectangle rectangle;
    
    int width;
    int height;

    int size;
    int stride;

    std::unique_ptr<const T*[]> z_values;
    std::list<int> nan_point_indices;

    ZMap(const std::map<Point2d, T>& data, const Rectangle& rectangle);

    Point2d GetPoint(int index) const;
    int GetIndex(int offset_x, int offset_y) const;
};

#include "../src/z_map.in"

#endif // __Z_MAP_H__