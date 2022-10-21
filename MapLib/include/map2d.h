// Created by 

#ifndef __MAP2D_H__
#define __MAP2D_H__

#include <vector>

// Represent map data
struct Map2d {
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
    std::vector<std::vector<double>> data;
};

#endif // __MAP2D_H__