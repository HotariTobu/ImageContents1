// Created by HotariTobu

#include "../include/indexed_point2d.h"

const Point2d& IndexedPoint2d::operator*() const noexcept {
    return *point;
}

const Point2d* IndexedPoint2d::operator->() const noexcept {
    return point;
}

bool operator==(const IndexedPoint2d& point1, const IndexedPoint2d& point2) noexcept {
    return point1.index == point2.index;
}

bool operator!=(const IndexedPoint2d& point1, const IndexedPoint2d& point2) noexcept {
    return !(point1 == point2);
}
