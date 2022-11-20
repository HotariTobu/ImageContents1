// Created by HotariTobu

#include "../include/indexed_point.h"

const Point2d& IndexedPoint::operator*() const noexcept {
    return *point;
}

const Point2d* IndexedPoint::operator->() const noexcept {
    return point;
}

bool operator==(const IndexedPoint& point1, const IndexedPoint& point2) noexcept {
    return point1.index == point2.index;
}

bool operator!=(const IndexedPoint& point1, const IndexedPoint& point2) noexcept {
    return !(point1 == point2);
}
