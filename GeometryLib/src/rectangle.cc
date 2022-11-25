// Created by HotariTobu

#include "../include/rectangle.h"

#include <limits>

Rectangle::Rectangle() {
    this->min_x = std::numeric_limits<double>::max();
    this->min_y = std::numeric_limits<double>::max();
    this->max_x = -std::numeric_limits<double>::max();
    this->max_y = -std::numeric_limits<double>::max();
}

Rectangle::Rectangle(double min_x, double min_y, double max_x, double max_y) {
    this->min_x = min_x;
    this->min_y = min_y;
    this->max_x = max_x;
    this->max_y = max_y;
}