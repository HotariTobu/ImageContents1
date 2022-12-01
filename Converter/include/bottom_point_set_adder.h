// Created by HotariTobu

#ifndef __BOTTOM_POINT_SET_ADDER_H__
#define __BOTTOM_POINT_SET_ADDER_H__

#include <list>
#include <map>

#include "attribute.h"
#include "point2d.h"
#include "rectangle.h"
#include "../include/index_set.h"

void AddBottomPointSet(const std::map<Point2d, Attribute>& data, Rectangle rectangle, std::list<std::pair<Point2d, double>>& additional_points, std::list<IndexSet>& additional_index_set_list, const std::list<std::pair<IndexSet, int>>& bottom_index_set_list);

#endif // __BOTTOM_POINT_SET_ADDER_H__