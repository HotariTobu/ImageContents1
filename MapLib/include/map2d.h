// Created by 

#ifndef __MAP2D_H__
#define __MAP2D_H__

#include <vector>

/*
Represent map data. `T` is the type of values.
Outside values with 1 width are nan and actual heights surrounded by them so the size of `Map2d::data` is (`Map2d::height` + 2) * (`Map2d::width` + 2).
*/
template<class T>
struct Map2d {
    // Min X value.
    int x;

    // Min Y value.
    int y;

    // Horizontal point count.
    int width;

    // Vertical point count.
    int height;

    /*
    Values of map.
    1st dimension: Y-axis direction
    2nd dimension: X-axis direction
    value = data[Y][X]
    */
    std::vector<std::vector<T>> data;
};

#endif // __MAP2D_H__