// Created by 

#ifndef __NEIGHBOR_H__
#define __NEIGHBOR_H__

// Represent 3x3 values.
struct Neighbor {
    /*
    Z values of neighbor.
    1st dimension: Y-axis direction
    2nd dimension: X-axis direction
    Z = data[Y][X]
    */
    double data[3][3];
};

#endif // __NEIGHBOR_H__