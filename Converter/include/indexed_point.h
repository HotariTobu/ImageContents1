// Created by HotariTobu

#ifndef __INDEXED_POINT_H__
#define __INDEXED_POINT_H__

#include <array>

#include "point2d.h"

struct IndexedPoint {
    int index;
    const Point2d* point;

    const Point2d& operator*() const noexcept;
    const Point2d* operator->() const noexcept;
};

bool operator==(const IndexedPoint& point1, const IndexedPoint& point2) noexcept;
bool operator!=(const IndexedPoint& point1, const IndexedPoint& point2) noexcept;

using IndexedPointSet = std::array<IndexedPoint, 3>;

#endif // __INDEXED_POINT_H__