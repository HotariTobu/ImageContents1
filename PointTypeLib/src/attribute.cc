// Created by HotariTobu

#include "../include/attribute.h"

#include <limits>

Attribute::Attribute() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    this->z = nan;
    this->type = PointType::NONE;
}

Attribute::Attribute(double z, PointType type) {
    this->z = z;
    this->type = type;
}

std::istream& operator>>(std::istream& is, Attribute& attribute) {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    if (!is.good()) {
        attribute.z = nan;
        attribute.type = PointType::NONE;
        return is;
    }

    is >> attribute.z;

    if (!is.good()) {
        attribute.type = PointType::NONE;
        return is;
    }

    int type;
    is >> type;
    attribute.type = static_cast<PointType>(type);
    
    return is;
}

std::ostream& operator<<(std::ostream& os, Attribute& attribute) {
    return os << attribute.z << static_cast<int>(attribute.type);
}