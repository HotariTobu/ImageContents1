// Created by HotariTobu

#ifndef __INDEXED_POINT2D_H__
#define __INDEXED_POINT2D_H__

#include <array>

#include "point2d.h"

struct IndexedPoint2d {
    int index;
    const Point2d* point;

    const Point2d& operator*() const noexcept;
    const Point2d* operator->() const noexcept;
};

bool operator==(const IndexedPoint2d& point1, const IndexedPoint2d& point2) noexcept;
bool operator!=(const IndexedPoint2d& point1, const IndexedPoint2d& point2) noexcept;

using IndexedPoint2dSet = std::array<IndexedPoint2d*, 3>;

#endif // __INDEXED_POINT2D_H__