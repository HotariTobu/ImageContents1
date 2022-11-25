// Created by HotariTobu

#include <iostream>
#include <string>

#include "../include/attribute.h"

int main() {
    Attribute attribute(3.14, PointType::GROUND);
    std::cout << ' ' << attribute << std::endl;
}