// Created by HotariTobu

#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <iostream>

class Color {
public:
	double r, g, b;

	Color();
	Color(double h, double s, double v);
};

std::istream& operator>>(std::istream& is, Color& color);
std::ostream& operator<<(std::ostream& os, const Color& color);

#endif
