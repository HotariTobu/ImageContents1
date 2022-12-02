// Created by HotariTobu

#ifndef __BOTTOM_POINT_SET_ADDER_H__
#define __BOTTOM_POINT_SET_ADDER_H__

#include <list>
#include <map>

#include "attribute.h"
#include "point2d.h"
#include "rectangle.h"
#include "../include/index_set.h"

void AddBottomPointSet(const std::map<Point2d, Attribute>& data, std::list<std::pair<Point2d, double>>& additional_points, std::list<IndexSet>& additional_index_set_list, std::list<std::pair<Point2d, int>>& border_indexed_points);

#endif // __BOTTOM_POINT_SET_ADDER_H__