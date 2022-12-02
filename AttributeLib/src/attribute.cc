// Created by HotariTobu

#include "../include/attribute.h"

#include <limits>

Attribute::Attribute() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    this->z = nan;
}

Attribute::Attribute(double z, Color color) {
    this->z = z;
    this->color = color;
}

std::istream& operator>>(std::istream& is, Attribute& attribute) {
    if (!is.good()) {
        return is;
    }

    return is >> attribute.z >> attribute.color;
}

std::ostream& operator<<(std::ostream& os, const Attribute& attribute) {
    return os << attribute.z << ' ' << attribute.color;
}