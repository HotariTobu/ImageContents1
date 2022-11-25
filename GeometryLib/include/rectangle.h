// Created by HotariTobu

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

struct Rectangle {
    double min_x;
    double min_y;
    double max_x;
    double max_y;

    Rectangle();
    Rectangle(double min_x, double min_y, double max_x, double max_y);
};

#endif // __RECTANGLE_H__