// Created by HotariTobu

#include "../include/near.h"

#include <cmath>

bool Near(double a, double b) {
    return std::fabs(a - b) < 0.00001;
}