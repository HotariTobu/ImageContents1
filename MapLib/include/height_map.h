// Created by 

#ifndef __HEIGHT_MAP_H__
#define __HEIGHT_MAP_H__

#include <vector>

// Represent map data
struct HeightMap {
    // Horizontal point count.
    int width;

    // Vertical point count.
    int height;

    /*
    Z values of map.
    1st dimension: Y-axis direction
    2nd dimension: X-axis direction
    Z = data[Y][X]
    */
    std::vector<std::vector<double>> data;
};

#endif // __HEIGHT_MAP_H__