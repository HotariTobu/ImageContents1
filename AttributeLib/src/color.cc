// Created by HotariTobu

#include "../include/color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(double h, double s, double v) {
    double max = v;
    double range = s * max;
    double min = max - range;

    int hd = h * 6;

    double rgb[] = { 0.0, 0.0, 0.0 };
    rgb[(int)((hd + 1) / 2) % 3] = max;
    rgb[(int)((hd + 4) / 2) % 3] = min;
    rgb[(7 - hd) % 3] = ((hd % 2 * -2 + 1) * (h * 6 - hd - 0.5) + 0.5) * range + min;

    r = rgb[0];
    g = rgb[1];
    b = rgb[2];
}

std::istream& operator>>(std::istream& is, Color& color) {
    double* rgb[3] = {&color.r, &color.g, &color.b};

    for (int i = 0; i < 3; ++i) {
        if (!is.good()) {
            return is;
        }

        is >> *rgb[i];
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << color.r << ' ' << color.g << ' ' << color.b;
}