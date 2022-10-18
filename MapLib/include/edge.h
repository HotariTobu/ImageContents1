// Created by 

#ifndef __EDGE_H__
#define __EDGE_H__

// Represent 3x3 values.
struct Edge {
    /*
    Z values of edge.
    1st dimension: Y-axis direction
    2nd dimension: X-axis direction
    Z = data[Y][X]
    */
    double data[3][3];
};

#endif // __EDGE_H__