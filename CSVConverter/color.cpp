#include "color.hpp"

Color::Color(double h, double s, double v) {
    h = h < 1 ? h : 0;

    double max = v;
    double range = s * max;
    double min = max - range;

    int hd = (int)(h * 6.0) % 6;
    int hdd = (int)(h * 3.0) % 3;

    double rgb[] = { 0.0, 0.0, 0.0 };
    rgb[hdd] = max;
    rgb[((hd + 1) / 2 + 1) % 3] = min;
    rgb[(5 - hd) % 3] = (hd % 2 == 0 ? -1.0 : 1.0) * (h * 6.0 - (double)(hdd) * 2.0 - 1.0) * range + min;

    r = rgb[0];
    g = rgb[1];
    b = rgb[2];
}
