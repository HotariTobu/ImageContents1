// Created by HotariTobu

#ifndef __NEIGHBOR_H__
#define __NEIGHBOR_H__

// Represent 3x3 values.
template<typename T>
struct Neighbor {
    const T** head;
    int stride;

    Neighbor(int stride);

    bool At(int x, int y, T* v) const;
    bool IsAllNull() const;
};

template<typename T>
bool operator==(const Neighbor<T> neighbor1, const Neighbor<T> neighbor2);
template<typename T>
bool operator!=(const Neighbor<T> neighbor1, const Neighbor<T> neighbor2);

#include "../src/neighbor.in"

#endif // __NEIGHBOR_H__