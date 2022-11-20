// Created by HotariTobu

#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <iostream>

#include "point_type.h"

struct Attribute {
    double z;
    PointType type;
};

std::istream& operator>>(std::istream& is, Attribute& attribute);
std::ostream& operator<<(std::ostream& os, Attribute& attribute);

#endif // __ATTRIBUTE_H__