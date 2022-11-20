// Created by HotariTobu

#include "../include/attribute.h"

std::istream& operator>>(std::istream& is, Attribute& attribute) {
    int type;
    is >> attribute.z >> type;
    attribute.type = static_cast<PointType>(type);
    return is;
}

std::ostream& operator<<(std::ostream& os, Attribute& attribute) {
    return os << attribute.z << static_cast<int>(attribute.type);
}