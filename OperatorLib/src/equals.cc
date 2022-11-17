// Created by HotariTobu

#include "../include/equals.h"

#include <cmath>

bool Equals(double a, double b) {
    return (a == b) || (std::isnan(a) && std::isnan(b));
}