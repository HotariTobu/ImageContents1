// Created by HotariTobu

#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <iostream>

#include "color.h"

struct Attribute {
    double z;
    Color color;

    Attribute();
    Attribute(double z, Color color);
};

std::istream& operator>>(std::istream& is, Attribute& attribute);
std::ostream& operator<<(std::ostream& os, const Attribute& attribute);

#endif // __ATTRIBUTE_H__