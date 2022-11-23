// Created by HotariTobu

#ifndef __NEIGHBOR_H__
#define __NEIGHBOR_H__

// Represent 3x3 values.
struct Neighbor {
    const double* head;
    int stride;

    Neighbor(int stride);

    bool At(int x, int y, double* z) const;
    bool IsAllNull() const;
};

bool operator==(const Neighbor neighbor1, const Neighbor neighbor2);
bool operator!=(const Neighbor neighbor1, const Neighbor neighbor2);

#endif // __NEIGHBOR_H__