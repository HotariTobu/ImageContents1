// Created by HotariTobu

#include <iostream>
#include <string>

#include "../include/attribute.h"

int main() {
    Color color(1, 1, 1);
    Attribute attribute(3.14, color);
    std::cout << ' ' << attribute << std::endl;
}