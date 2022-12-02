// Created by HotariTobu

#ifndef __BOTTOM_POINT_SET_REMOVER_H__
#define __BOTTOM_POINT_SET_REMOVER_H__

#include <list>

#include "rectangle.h"
#include "../include/index_set.h"
#include "../include/indexed_point2d.h"

std::list<std::pair<Point2d, int>> RemoveBottomPointSet(std::list<IndexedPoint2dSet>& leaf_point_set_list, const Rectangle& rectangle);

#endif // __BOTTOM_POINT_SET_REMOVER_H__